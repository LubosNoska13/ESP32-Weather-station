import os
import secrets
from PIL import Image
from flask import current_app
from weather_station.models import Users

def save_picture(form_picture):
    ## Generate random name for picture
    random_hex = secrets.token_hex(8)
    _, f_extension = os.path.splitext(form_picture.filename)
    picture_name = random_hex + f_extension
    
    picture_path = os.path.join(current_app.root_path, "static/images/profile_pics", picture_name)
    
    output_size = (170, 170)
    image = Image.open(form_picture)
    image.thumbnail(output_size)
    
    image.save(picture_path)
    return picture_name

def remove_unnecessary_images():
    users_images = os.listdir(os.path.join(current_app.root_path, "static/images/profile_pics/"))
    print(Users.query.count())
    if Users.query.count() + 1 >= len(users_images):
        print("Remove img:")
        database_images = (user.image_file for user in Users.query.all())
        
        unnecessary_images = set(users_images) - set(database_images)
        # Remove unnecessary images
        for image in unnecessary_images:
            if image != "default.jpg":
                print(image)
                os.remove(os.path.join(current_app.root_path, f"static/images/profile_pics/{image}"))