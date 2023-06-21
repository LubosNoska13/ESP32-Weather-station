//! Toggle menu with hamburger 
hamburger_menu = document.querySelector(".hamburger-menu");
big_wrapper = document.querySelector(".welcome-page-wrapper");

hamburger_menu.addEventListener("click", () => {
    big_wrapper.classList.toggle("active");
});