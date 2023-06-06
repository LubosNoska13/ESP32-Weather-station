from flask import Blueprint, render_template, url_for, flash, redirect, request, abort
from flask_login import current_user, login_required
from weather_station import db
from weather_station.models import Posts, Users
from weather_station.posts.forms import PostForm

posts = Blueprint("posts", __name__)

@posts.route("/posts")
@login_required
def all_posts():
    ## Get page number in url
    page = request.args.get("page", default=1, type=int)
    
    ## Show only 5 posts per page
    posts = Posts.query.order_by(Posts.date_posted.desc()).paginate(per_page=4, page=page)
    return render_template("all_posts.html", title="Posts", posts=posts)


@posts.route("/posts/new", methods=["GET", "POST"])
@login_required
def create_post():
    form = PostForm()
    
    if form.validate_on_submit():
        post = Posts(title=form.title.data, content=form.content.data, author=current_user)
        
        db.session.add(post)
        db.session.commit()
        
        flash("Your post has been created!", "success")
        return redirect(url_for("posts.all_posts"))
    
    return render_template("create_post.html", title="Create Post", form=form, legend="New Post")


@posts.route("/specific_post/<int:post_id>")
@login_required
def specific_post(post_id):
    post = Posts.query.get_or_404(post_id)
    return render_template('specific_post.html', title=post.title, post=post)


@posts.route("/specific_post/<int:post_id>/update", methods=["GET", "POST"])
@login_required
def update_post(post_id):
    post = Posts.query.get_or_404(post_id)
    if current_user.is_admin or post.author == current_user:
        pass
    else:
        abort(403)
    
    form = PostForm()
    if form.validate_on_submit():
        ## Update changes
        post.title = form.title.data
        post.content = form.content.data
        db.session.commit()
        flash("Your post has been updated!", "success")
        return redirect(url_for("posts.specific_post", post_id=post.id))
    
    elif request.method == "GET":
        ## Fill out form
        form.title.data = post.title
        form.content.data = post.content
    return render_template("create_post.html", title="Update Post", form=form, legend="Update Post")


@posts.route("/specific_post/<int:post_id>/delete", methods=["POST"])
@login_required
def delete_post(post_id):
    post = Posts.query.get_or_404(post_id)
    if current_user.is_admin or post.author == current_user:
        pass
    else:
        abort(403)
        
    db.session.delete(post)
    db.session.commit()
    
    flash("Your post has been deleted!", "success")
    return redirect(url_for("posts.all_posts"))


@posts.route("/user/<string:username>")
@login_required
def user_posts(username):
    ## Get page number in url
    page = request.args.get("page", default=1, type=int)
    
    user = Users.query.filter_by(username=username).first_or_404()
    
    ## Show only 5 posts per page
    posts = Posts.query.filter_by(author=user).order_by(Posts.date_posted.desc()).paginate(per_page=4, page=page)
    return render_template("user_posts.html", title="User Posts", posts=posts, user=user)

