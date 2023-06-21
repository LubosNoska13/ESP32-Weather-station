from flask import Blueprint, render_template, abort
from flask_login import login_required, current_user
from weather_station.models import Weather

main = Blueprint("main", __name__)


@main.route("/")
@main.route("/home")
def home():
    return render_template("index.html", title="Home")


@main.route("/dashboard")
@login_required
def dashboard():
    return render_template("dashboard.html", title="Dashboard") 

@main.route("/data")
@login_required
def data():
    if current_user.is_admin is False:
        abort(403)
    database = Weather.query.order_by(Weather.date.desc()).all()
    return render_template("data.html", database=database)