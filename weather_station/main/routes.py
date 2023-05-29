from flask import Blueprint, render_template
from weather_station.models import Posts
from flask_login import login_required

main = Blueprint("main", __name__)

@main.context_processor 
def recent_posts():
    r_posts = Posts.query.order_by(Posts.date_posted.desc()).limit(3)
    return dict(r_posts=r_posts)


@main.route("/")
@main.route("/home")
def home():
    return render_template("index.html", title="Home")


@main.route("/dashboard")
@login_required
def dashboard():
    return render_template("dashboard.html", title="Dashboard") 