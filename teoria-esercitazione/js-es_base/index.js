const but = document.getElementById("but");
const input = document.getElementById("input");
const result = document.getElementById("div2");
const colors = ["color-black", "color-cyan", "color-magenta", "color-yellow"];

but.addEventListener("click", () => {
    const times = parseInt(input.value);

    if (typeof times !== "number") {
        console.error("La stringa non è un numero!");
        
        return;
    }

    let text = "";

    for (let i = 0; i < times; i++) {
        text += `<span id="${i}">Ciao</span>`
    }
    
    result.innerHTML = text;
    result.classList.remove("not-visible");

    for (let i = 0; i < times; i++) {
        const span = document.getElementById(`${i}`);
        const number_random = Math.floor(Math.random() * 4);
        span.classList.add(colors[number_random]);
    }
});