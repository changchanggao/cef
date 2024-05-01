document.write(location.href);
window.onbeforeunload = function () {
    return "askForClose"
}