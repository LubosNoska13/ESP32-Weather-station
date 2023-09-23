//! Toggle menu with hamburger 
const sideMenu = document.querySelector("aside");
const menuBtn = document.querySelector("#menu-btn");
const closeBtn = document.querySelector("#close-btn");

menuBtn.addEventListener("click", () => {
    sideMenu.style.display = "block";
})

closeBtn.addEventListener("click", () => {
    sideMenu.style.display = "none";
})

//! Change theme
const themeToggler = document.querySelector(".theme-toggler");
const body = document.querySelector('body');

themeToggler.addEventListener("click", () => {
    document.body.classList.toggle("dark-theme-variables");
    
    themeToggler.querySelector("svg:nth-child(1)").classList.toggle("active");
    themeToggler.querySelector("svg:nth-child(2)").classList.toggle("active");
    
    // Store the user's preference in the session
    fetch('/toggle_dark_mode', {
        method: 'POST',
        body: JSON.stringify({'dark_mode': body.classList.contains('dark-theme-variables')}),
        headers: {
            'Content-Type': 'application/json',
        }
    });
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
const articles = document.querySelectorAll(".article");

articles.forEach(article => {
    article.addEventListener("click", () => {
        const heart = article.querySelector(".heart");
        const postID = article.dataset.postId; // Retrieve the post_id from data attribute
        if(heart.classList.contains('like')) {
            heart.classList.remove('like');
            heart.classList.add('unlike');
        } else {
            heart.classList.remove('unlike');
            heart.classList.add('like');
        }
        // Store the user's preference in the session
        fetch('/toggle_article_like', {
            method: 'POST',
            body: JSON.stringify({'post_id':postID, 'article_like': heart.classList.contains('like')}),
            headers: {
                'Content-Type': 'application/json',
            }
        });
    });
});


//! Settings formular
const inputs = document.querySelectorAll(".contact-input");

inputs.forEach((ipt) => {
    if (ipt.value != ""){
        ipt.parentNode.classList.add("not-empty");
    }

    ipt.addEventListener("focus", () => {
        ipt.parentNode.classList.add("focus");
        ipt.parentNode.classList.add("not-empty");
    });
    ipt.addEventListener("blur", () => {
        if (ipt.value == ""){
            ipt.parentNode.classList.remove("not-empty");
        }
        ipt.parentNode.classList.remove("focus");
    });
});
