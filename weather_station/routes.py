from flask import render_template, flash, redirect, url_for, request
from weather_station import app
from weather_station.forms import RegistrationForm, LoginForm
from weather_station.models import Users, Posts


@app.route("/")
@app.route("/home")
def home():
    return render_template("index.html", title="Home")

@app.route("/login", methods=["GET", "POST"])
def login():
    login_form = LoginForm()
    
    if login_form.validate_on_submit():
        flash("You have been login successfully!", "success")
        return redirect(url_for("dashboard"))
    
    return render_template("login.html", title="Login", form=login_form)


@app.route("/register", methods=["GET", "POST"])
def register():
    register_form = RegistrationForm()
    
    if register_form.validate_on_submit():
        flash("You have been registered successfully!", "success")
        return redirect(url_for("dashboard"))
    
    return render_template("register.html", title="Register", form=register_form)


@app.route("/dashboard")
def dashboard():
    return render_template("dashboard.html", title="Dashboard")

@app.route("/posts")
def posts():
    return render_template("posts.html", title="Posts")
