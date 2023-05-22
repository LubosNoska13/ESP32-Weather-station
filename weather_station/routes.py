import os
import secrets
import json
from PIL import Image
from flask import render_template, flash, redirect, url_for, request, abort, jsonify
from weather_station import app, db, bcrypt, mqtt, mail
from weather_station.forms import RegistrationForm, LoginForm, UpdateAccountForm, PostForm
from weather_station.models import Users, Posts
from flask_login import login_user, current_user, logout_user, login_required
from flask_mail import Message
from weather_station.config import credentials
from weather_station.config import send_email

@app.context_processor 
def recent_posts():
    r_posts = Posts.query.order_by(Posts.date_posted.desc()).limit(3)
    return dict(r_posts=r_posts)


@app.route("/")
@app.route("/home")
def home():
    return render_template("index.html", title="Home")

@app.route("/login", methods=["GET", "POST"])
def login():
    if current_user.is_authenticated:
        return redirect(url_for("dashboard"))
    
    login_form = LoginForm()
    if login_form.validate_on_submit():
        
        ## Check if the user is in the database and type right password
        user = Users.query.filter_by(email=login_form.email.data).first()
        if user and bcrypt.check_password_hash(user.password, login_form.password.data):
            
            ## Login user
            login_user(user)
            
            ## Flash message
            flash("You have been login successfully!", "success")
            
            ## Check if you try to access some page without login,
            ## if so it will redirect you into that page after login
            next_page = request.args.get("next")
            
            return redirect(next_page) if next_page else redirect(url_for("dashboard"))
        
        else:
            ## Flash message
            flash("Login unsuccessful. Please check email and password!", "danger")
        
    return render_template("login.html", title="Login", form=login_form)


@app.route("/register", methods=["GET", "POST"])
def register():
    if current_user.is_authenticated:
        return redirect(url_for("dashboard"))
    
    register_form = RegistrationForm()
    if register_form.validate_on_submit():
        ## Hash password
        hashed_password = bcrypt.generate_password_hash(register_form.password.data).decode("utf-8")
        
        ## Create user instance
        user = Users(username=register_form.username.data, email=register_form.email.data, password=hashed_password)
        
        ## Add user to database
        db.session.add(user)
        db.session.commit()
        
        ## Flash message
        flash("You have been registered successfully! You can login into your account.", "success")
        
        return redirect(url_for("login"))
    
    return render_template("register.html", title="Register", form=register_form)


@app.route("/dashboard")
@login_required
def dashboard():
    return render_template("dashboard.html", title="Dashboard", posts=posts)


@app.route("/posts")
@login_required
def posts():
    ## Get page number in url
    page = request.args.get("page", default=1, type=int)
    
    ## Show only 5 posts per page
    posts = Posts.query.order_by(Posts.date_posted.desc()).paginate(per_page=4, page=page)
    return render_template("posts.html", title="Posts", posts=posts)

@app.route("/posts/new", methods=["GET", "POST"])
@login_required
def create_post():
    form = PostForm()
    
    if form.validate_on_submit():
        post = Posts(title=form.title.data, content=form.content.data, author=current_user)
        
        db.session.add(post)
        db.session.commit()
        
        flash("Your post has been created!", "success")
        return redirect(url_for("posts"))
    
    return render_template("create_post.html", title="Create Post", form=form, legend="New Post")


@app.route("/specific_post/<int:post_id>")
@login_required
def specific_post(post_id):
    post = Posts.query.get_or_404(post_id)
    return render_template('specific_post.html', title=post.title, post=post)


@app.route("/specific_post/<int:post_id>/update", methods=["GET", "POST"])
@login_required
def update_post(post_id):
    post = Posts.query.get_or_404(post_id)
    if post.author != current_user:
        abort(403)
    
    form = PostForm()
    if form.validate_on_submit():
        ## Update changes
        post.title = form.title.data
        post.content = form.content.data
        db.session.commit()
        flash("Your post has been updated!", "success")
        return redirect(url_for("specific_post", post_id=post.id))
    
    elif request.method == "GET":
        ## Fill out form
        form.title.data = post.title
        form.content.data = post.content
    return render_template("create_post.html", title="Update Post", form=form, legend="Update Post")


@app.route("/specific_post/<int:post_id>/delete", methods=["POST"])
@login_required
def delete_post(post_id):
    post = Posts.query.get_or_404(post_id)
    if post.author != current_user:
        abort(403)
        
    db.session.delete(post)
    db.session.commit()
    
    flash("Your post has been deleted!", "success")
    return redirect(url_for("posts"))


@app.route("/user/<string:username>")
@login_required
def user_posts(username):
    ## Get page number in url
    page = request.args.get("page", default=1, type=int)
    
    user = Users.query.filter_by(username=username).first_or_404()
    
    ## Show only 5 posts per page
    posts = Posts.query.filter_by(author=user).order_by(Posts.date_posted.desc()).paginate(per_page=4, page=page)
    return render_template("user_posts.html", title="User Posts", posts=posts, user=user)


def save_picture(form_picture):
    ## Generate random name for picture
    random_hex = secrets.token_hex(8)
    _, f_extension = os.path.splitext(form_picture.filename)
    picture_name = random_hex + f_extension
    
    picture_path = os.path.join(app.root_path, "static/images/profile_pics", picture_name)
    
    output_size = (170, 170)
    image = Image.open(form_picture)
    image.thumbnail(output_size)
    
    image.save(picture_path)
    return picture_name


@app.route("/settings", methods=["GET", "POST"])
@login_required
def settings():
    update_form = UpdateAccountForm()
    if update_form.validate_on_submit():
        
        if update_form.image_file.data:
            image_file = save_picture(update_form.image_file.data)
            current_user.image_file = image_file
            
        current_user.username = update_form.username.data
        current_user.email = update_form.email.data
        db.session.commit()
        
        flash("Your account has been updated!", "success")
        return redirect(url_for("settings"))
    
    elif request.method == "GET":
        update_form.username.data = current_user.username
        update_form.email.data = current_user.email
        
    image_file = url_for("static", filename=f"images/profile_pics/{current_user.image_file}")
    return render_template("settings.html", title="Settings", image_file=image_file, form=update_form)


@app.route("/logout")
def logout():
    
    ## Logout user
    logout_user()
    return redirect(url_for("home"))

data_list = []

@mqtt.on_message()
def on_message(client, userdata, message):
    # Extract the subscription topic from the message
    topic = message.topic
    
    if topic == "esp32/data":
        
        # Process the received message
        payload = message.payload.decode("utf-8")
        data = json.loads(payload)
        
        with app.app_context():  # create a Flask application context
            
            # Send email
            if data.get("temperature") > send_email.SEND_EMAIL_TEMPERATURE:
                msg = Message(send_email.EMAIL_TEMPERATURE_HEAD, sender=credentials.EMAIL, recipients=credentials.EMAIL_RECEIVERS)
                msg.body = send_email.EMAIL_TEMPERATURE_CONTENT.format(data.get("temperature"))
                mail.send(msg)
                send_email.SEND_EMAIL_TEMPERATURE += 1
                print("Email sent")
        
        print(data)
        
        # Only return the most recent 10 records
        if len(data_list) > 7:
            data_list.pop(0)
        
        # Append the received data to the data_list
        data_list.append(data)


@app.route('/esp32/data')
def data_esp32():
    return jsonify(data_list)


@app.route("/weather")
def weather():
    return render_template("weather.html")
