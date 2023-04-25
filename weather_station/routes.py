import os
import secrets
from PIL import Image
from flask import render_template, flash, redirect, url_for, request
from weather_station import app, db, bcrypt
from weather_station.forms import RegistrationForm, LoginForm, UpdateAccountForm
from weather_station.models import Users, Posts
from flask_login import login_user, current_user, logout_user, login_required


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
    return render_template("dashboard.html", title="Dashboard")


@app.route("/posts")
@login_required
def posts():
    return render_template("posts.html", title="Posts")


def save_picture(form_picture):
    ## Generate random name for picture
    random_hex = secrets.token_hex(8)
    _, f_extension = os.path.splitext(form_picture.filename)
    picture_name = random_hex + f_extension
    
    picture_path = os.path.join(app.root_path, "static/images/profile_pics", picture_name)
    
    output_size = (125, 125)
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