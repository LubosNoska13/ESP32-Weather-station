from flask_wtf import FlaskForm
from wtforms import StringField, PasswordField, SubmitField, EmailField
from wtforms.validators import DataRequired, Length, Email, EqualTo, ValidationError
from weather_station.models import Users

class RegistrationForm(FlaskForm):
    username = StringField("Name", validators=[DataRequired(), Length(min=2, max=20)], render_kw={"placeholder": "Username"})
    email = EmailField("Email", validators=[DataRequired()], render_kw={"placeholder": "Email"})
    password = PasswordField("Password", validators=[DataRequired(), Length(min=6, max=20)], render_kw={"placeholder": "Password"})
    confirm_password = PasswordField("Confirm Password", validators=[DataRequired(), Length(min=6, max=20), EqualTo("password", message="Passwords must match!")], render_kw={"placeholder": "Confirm"})
    submit = SubmitField("Sign Up")
    
    def validate_username(self, username):
        user = Users.query.filter_by(username=username.data).first()
        if user:
            raise ValidationError("That username is taken. Please choose a different one.")
	
    def validate_email(self, email):
        user = Users.query.filter_by(email=email.data).first()
        if user:
            raise ValidationError("That email is taken. Please choose a different one.")


class LoginForm(FlaskForm):
    email = EmailField("Email", validators=[DataRequired()], render_kw={"placeholder": "Email"})
    password = PasswordField("Password", validators=[DataRequired(), Length(min=6, max=20)], render_kw={"placeholder": "Password"})
    submit = SubmitField("Login")

