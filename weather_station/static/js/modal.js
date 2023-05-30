
//! Close Model
const modal = document.querySelector("#modal")
const openModel = document.querySelector(".open-button");
const closeModel = document.querySelector(".close-button");

openModel.addEventListener("click", () => {
    modal.showModal();
});

closeModel.addEventListener("click", () => {
    modal.close();
});