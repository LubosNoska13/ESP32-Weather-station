from flask import Flask, render_template

app = Flask(__name__)
app.config["DEBUG"] = True

@app.route("/")
@app.route("/home")
def home():
    return render_template("index.html", title="Home")

@app.route("/login", methods=["GET", "POST"])
def login():
    return render_template("login.html", title="Login")

@app.route("/dashboard")
def dashboard():
    return render_template("dashboard.html", title="Dashboard")

@app.route("/posts")
def posts():
    return render_template("posts.html", title="Posts")

if __name__ == "__main__":
    app.run()