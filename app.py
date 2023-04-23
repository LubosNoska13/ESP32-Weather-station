from flask import Flask, render_template, flash, redirect, url_for
import credentials
from forms import RegistrationForm, LoginForm

app = Flask(__name__)
app.config["DEBUG"] = True
app.config["SECRET_KEY"] = credentials.SECRET_KEY

@app.route("/")
@app.route("/home")
def home():
    return render_template("index.html", title="Home")

@app.route("/login", methods=["GET", "POST"])
def login():
    register_form = RegistrationForm()
    login_form = LoginForm()
    
    if login_form.validate_on_submit():
        flash("You have been login successfully!")
        print(login_form.email.data)
        print(login_form.password.data)
        return redirect(url_for("dashboard"))
    
    elif register_form.validate_on_submit():
        flash("Register")
        print(register_form.username.data)
        print(register_form.email.data)
        return redirect(url_for("dashboard"))
    return render_template("login.html", title="Login", login_form=login_form, register_form=register_form)


@app.route("/dashboard")
def dashboard():
    return render_template("dashboard.html", title="Dashboard")

@app.route("/posts")
def posts():
    return render_template("posts.html", title="Posts")



if __name__ == "__main__":
    app.run()