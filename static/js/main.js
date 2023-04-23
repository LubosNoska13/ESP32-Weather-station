//! Toggle menu with hamburger 
hamburger_menu = document.querySelector(".hamburger-menu");
big_wrapper = document.querySelector(".welcome-page-wrapper");

hamburger_menu.addEventListener("click", () => {
    big_wrapper.classList.toggle("active");
});

//! Toggle menu with hamburger 
const sideMenu = document.querySelector("aside");
const menuBtn = document.querySelector("#menu-btn");
const closeBtn = document.querySelector("#close-btn");

menuBtn.addEventListener("click", () => {
    sideMenu.style.display = "block";
    console.log("hello")
})

closeBtn.addEventListener("click", () => {
    sideMenu.style.display = "none";
})

//! Change theme
const themeToggler = document.querySelector(".theme-toggler");

themeToggler.addEventListener("click", () => {
    document.body.classList.toggle("dark-theme-variables");
    
    themeToggler.querySelector("svg:nth-child(1)").classList.toggle("active");
    themeToggler.querySelector("svg:nth-child(2)").classList.toggle("active");
})

const links = document.querySelectorAll('.sidebar a');

links.forEach(link => {
    link.addEventListener('click', function() {
    // Remove the "active" class from all links
    links.forEach(link => {
        link.classList.remove('active');
    });
    // Add the "active" class to the clicked link
    this.classList.add('active');
    
    });
});


//! Beating heart
const articles = document.querySelectorAll(".article")

articles.forEach(article => {
    article.addEventListener("click", () => {
    const heart = article.querySelector(".heart");

    if(heart.classList.contains('like')) {
        heart.classList.remove('like');
        heart.classList.add('unlike');
    } else {
        heart.classList.remove('unlike');
        heart.classList.add('like');
    }
    });
});