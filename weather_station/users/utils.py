import os
import secrets
from PIL import Image
from weather_station import app
from weather_station.models import Users

def save_picture(form_picture):
    ## Generate random name for picture
    random_hex = secrets.token_hex(8)
    _, f_extension = os.path.splitext(form_picture.filename)
    picture_name = random_hex + f_extension
    
    picture_path = os.path.join(app.root_path, "static/images/profile_pics", picture_name)
    
    output_size = (170, 170)
    image = Image.open(form_picture)
    image.thumbnail(output_size)
    
    image.save(picture_path)
    return picture_name

def remove_unnecessary_images():
    users_images = os.listdir(os.path.normpath("static/images/profile_pics/"))
    if Users.query.count() + 1 > len(users_images):
        database_images = (user.image_file for user in Users.query.all() if user.image_file != "default.jpg")
        
        unnecessary_images = set(database_images) - set(users_images)
        # Remove unnecessary images
        #for image in unnecessary_images:
        #    os.remove(os.path.normpath(f"static/images/profile_pics/{image}"))