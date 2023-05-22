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


//! Close Model
// const modal = document.querySelector("#modal")
// const openModel = document.querySelector(".open-button");
// const closeModel = document.querySelector(".close-button");

// openModel.addEventListener("click", () => {
//     modal.showModal();
// });

// closeModel.addEventListener("click", () => {
//     modal.close();
// });


const temperatureSpan = document.querySelector("#stream-temperature-value");
const humiditySpan = document.querySelector("#stream-humidity-value");

function updateValues() {
    fetch('/esp32/data')
        .then(response => response.json())
        .then(data => {
        
        
        const temperature = parseFloat(data.pop()["temperature"].toFixed(2));
        const humidity = data.pop()["humidity"];
        
        temperatureSpan.innerHTML = temperature;
        humiditySpan.innerHTML = humidity;
        
    });
}

setInterval(updateValues, 2000);


function setThemePreference() {
    const themePreference = localStorage.getItem('themePreference');

    console.log(themePreference);

    if (themePreference === 'dark') {
        document.documentElement.setAttribute('data-theme', 'dark');
    } else {
        document.documentElement.setAttribute('data-theme', 'light');
    }
}

window.addEventListener('load', setThemePreference);