from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from flask_bcrypt import Bcrypt
from flask_login import LoginManager
from flask_mqtt import Mqtt
from flask_mail import Mail
from weather_station.config.config import Config

# App 
app = Flask(__name__)

# App config, Broker config, Email config
app.config.from_object(Config)

# Instances
db = SQLAlchemy(app)
bcrypt = Bcrypt(app)
login_manager = LoginManager()
login_manager.init_app(app)
login_manager.login_view = "users.login"  ## name of function
login_manager.login_message_category = "info"  ## class of flash message

mqtt = Mqtt(app)
mqtt.subscribe('esp32/data')

mail = Mail(app)

# Blueprints
from weather_station.users.routes import users
from weather_station.posts.routes import posts
from weather_station.main.routes import main
from weather_station.data.routes import data
from weather_station.data.api import api

app.register_blueprint(users)
app.register_blueprint(posts)
app.register_blueprint(main)
app.register_blueprint(data)
app.register_blueprint(api)