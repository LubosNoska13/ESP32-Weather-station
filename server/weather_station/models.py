from datetime import datetime
from weather_station import db, login_manager
from flask_login import UserMixin

@login_manager.user_loader 
def load_user(user_id):
    return Users.query.get(int(user_id))


class Users(db.Model, UserMixin):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(20), unique=True, nullable=False)
    email = db.Column(db.String(40), unique=True, nullable=False)
    image_file = db.Column(db.String(20), nullable=False, default="default.jpg")
    password = db.Column(db.String(70), nullable=False)
    is_admin = db.Column(db.Boolean, unique=False, default=False)
    dark_mode = db.Column(db.Boolean, unique=False, default=False)
    posts = db.relationship("Posts", backref="author", lazy=True)
    liked_posts = db.relationship("Likes", backref="user", lazy=True)
    
    def __repr__(self):
        return f"Users('{self.username}', '{self.email}', '{self.image_file}')"
    
    
class Posts(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    title = db.Column(db.String(100), nullable=False)
    date_posted = db.Column(db.DateTime, nullable=False, default=datetime.utcnow)
    content = db.Column(db.Text, nullable=False)
    user_id = db.Column(db.Integer, db.ForeignKey("users.id"), nullable=False)
    likes = db.relationship("Likes", backref="post", lazy=True)
    
    def __repr__(self):
        return f"Posts('{self.title}', '{self.date_posted}')"


class Likes(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    user_id = db.Column(db.Integer, db.ForeignKey("users.id"), nullable=False)
    post_id = db.Column(db.Integer, db.ForeignKey("posts.id"), nullable=False)
    like_value = db.Column(db.Boolean, unique=False, default=False) 


class Weather(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    date = db.Column(db.DateTime, nullable=False, default=datetime.now)
    values = db.Column(db.JSON, nullable=False)
    device = db.Column(db.String(25), nullable=False)
    
    def __repr__(self):
        return f"Weather('{self.date}', '{self.device}')"
