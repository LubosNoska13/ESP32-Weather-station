# Flask secret key
SECRET_KEY = ""
DATABASE_URI = ""

# Broker settings
MQTT_BROKER_URL = "" # Ip address of mqtt broker
MQTT_BROKER_PORT = 1883
MQTT_USERNAME = ""
MQTT_PASSWORD = ""
MQTT_KEEPALIVE = 5
MQTT_TLS_ENABLED = False

# Email Alert
EMAIL = "" # The email that will send alert messages
EMAIL_PASSWORD = ""
EMAIL_RECEIVERS = [""] # All emails that will receive the alert messages 
EMAIL_PORT = 465
EMAIL_USE_TLS = False
EMAIL_USE_SSL = True
EMAIL_SERVER = ''