function abre_nova_janela() {
    const oRotina = document.getElementById('rotina');
    const formData = new URLSearchParams();
    formData.append('rotina', oRotina.attributes['rotina'].value);
    formData.append('acao', oRotina.attributes['acao'].value);
    const busca = fetch('api/call_controller.php', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded'
        },
        body: formData
    });
    busca.then(() => response.json())
    .then(function(response) {
        
    });
}

function montaConsulta(dados) {
    const consulta = document.getElementById('consulta');
}

const janela = document.getElementById('janela');
let isDragging = false;
let offSetX;
let offSetY;

janela.addEventListener('mousedown', (e) => {
    if (e.target.tagName === 'HEADER') {
        isDragging = true;
        offsetX = e.clientX - janela.offsetLeft;
        offsetY = e.clientY - janela.offsetTop;
    }
});

document.addEventListener('mousemove', (e) => {
    if (isDragging) {
        janela.style.left = `${e.clientX - offsetX}px`;
        janela.style.top = `${e.clientY - offsetY}px`;
    }
});

document.addEventListener('mouseup', () => {
    isDragging = false;
});