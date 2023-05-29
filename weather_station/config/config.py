from weather_station.config import credentials

class Config:
    # App config
    SECRET_KEY = credentials.SECRET_KEY
    SQLALCHEMY_DATABASE_URI = credentials.DATABASE_URI
    
    # Broker config
    MQTT_BROKER_URL = credentials.MQTT_BROKER_URL  # use the free broker from HIVEMQ
    MQTT_BROKER_PORT = credentials.MQTT_BROKER_PORT  # default port for non-tls connection
    MQTT_USERNAME = credentials.MQTT_USERNAME  # set the username here if you need authentication for the broker
    MQTT_PASSWORD = credentials.MQTT_PASSWORD  # set the password here if the broker demands authentication
    MQTT_KEEPALIVE = credentials.MQTT_KEEPALIVE  # set the time interval for sending a ping to the broker to 5 seconds
    MQTT_TLS_ENABLED = credentials.MQTT_TLS_ENABLED  # set TLS to disabled for testing purposes

    # Email config
    MAIL_SERVER = credentials.EMAIL_SERVER
    MAIL_PORT = credentials.EMAIL_PORT
    MAIL_USERNAME = credentials.EMAIL
    MAIL_PASSWORD = credentials.EMAIL_PASSWORD
    MAIL_USE_TLS = credentials.EMAIL_USE_TLS
    MAIL_USE_SSL = credentials.EMAIL_USE_SSL