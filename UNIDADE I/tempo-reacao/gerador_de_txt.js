function copy() {
  const text = [];
  for (let index = 4; index <= 14; index += 2) {
    const p = document.querySelector(
      `#content > div.col-xs-12.col-md-8.card > p:nth-child(${index})`
    );
    if (p != null || p != undefined) {
      var palavras = p.innerHTML.trim().split("<br>");
      text.push(...palavras);
    }
  }

  function downloadFile(conteudo, filename) {
    var ancora = document.createElement("a");
    ancora.href =
      "data:application/octet-stream;charset=utf-8," +
      encodeURIComponent(conteudo);
    ancora.download = filename;
    ancora.click();
  }
  downloadFile(text, "text.txt");
}
copy();

function remover_acentos_espaco(str) {
  return str.normalize("NFD").replace(/[^a-zA-Z\s]/g, "");
}

const value = "ad";
text.filter((item) => {
  var text = remover_acentos_espaco(item);
  for (let index = 0; index < value.length; index++) {
    if (value[index] !== text[index]) {
      return;
    }
  }
  return item;
});
