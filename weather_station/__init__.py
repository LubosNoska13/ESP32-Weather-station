from weather_station.config import credentials
from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from flask_bcrypt import Bcrypt
from flask_login import LoginManager
from flask_mqtt import Mqtt
from flask_mail import Mail

app = Flask(__name__)
app.config["SECRET_KEY"] = credentials.SECRET_KEY
app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///site.db"

# Broker config
app.config['MQTT_BROKER_URL'] = credentials.MQTT_BROKER_URL  # use the free broker from HIVEMQ
app.config['MQTT_BROKER_PORT'] = credentials.MQTT_BROKER_PORT  # default port for non-tls connection
app.config['MQTT_USERNAME'] = credentials.MQTT_USERNAME  # set the username here if you need authentication for the broker
app.config['MQTT_PASSWORD'] = credentials.MQTT_PASSWORD  # set the password here if the broker demands authentication
app.config['MQTT_KEEPALIVE'] = credentials.MQTT_KEEPALIVE  # set the time interval for sending a ping to the broker to 5 seconds
app.config['MQTT_TLS_ENABLED'] = credentials.MQTT_TLS_ENABLED  # set TLS to disabled for testing purposes

# Email config
app.config['MAIL_SERVER']='smtp.gmail.com'
app.config['MAIL_PORT'] = 465
app.config['MAIL_USERNAME'] = credentials.EMAIL
app.config['MAIL_PASSWORD'] = credentials.EMAIL_PASSWORD
app.config['MAIL_USE_TLS'] = False
app.config['MAIL_USE_SSL'] = True

# Instances
db = SQLAlchemy(app)
bcrypt = Bcrypt(app)
login_manager = LoginManager()
login_manager.init_app(app)
login_manager.login_view = "login"  ## name of function
login_manager.login_message_category = "info"  ## class of flash message

mqtt = Mqtt(app)
mqtt.subscribe('esp32/data')

mail = Mail(app)

from weather_station import routes