document.cookie = 'XDEBUG_SESSION=VSCODE';

function abre_nova_janela(oChave, oParametros, oLink) {
    const oRotina = document.getElementById('rotina');
    loadAjax({
        rotina: oLink.rotina,
        acao: oLink.acao,
        completo: function(res) {
            
            const oJanela = new Janela({
                titulo: res.titulo
            });
            
            if (res.tipo == 1) {
                montaConsulta(res.dados);
            }
            if (res.tipo == 2) {
                montaManutencao(res.campos);
            }
        }
    });
}

var Janela = function(opt) {
    const divJanela = document.createElement('div');
    divJanela.className = 'janela';
    divJanela.id = 'janela';

    const header = document.createElement('header');
    header.textContent = opt.titulo;
    divJanela.appendChild(header);

    const divContent = document.createElement('div');
    divContent.className = 'content';
    divJanela.appendChild(divContent);

    const areaAcoes = document.createElement('div');
    areaAcoes.id = 'area_acoes';

    const botaoConfirmar = document.createElement('button');
    botaoConfirmar.id = 'botao_confirmar';
    botaoConfirmar.textContent = 'Confirmar';
    botaoConfirmar.onclick = function () {
      confirma_submit();
    };

    const botaoLimpar = document.createElement('button');
    botaoLimpar.id = 'botao_limpar';
    botaoLimpar.textContent = 'Limpar';

    const botaoFechar = document.createElement('button');
    botaoFechar.id = 'botao_fechar';
    botaoFechar.textContent = 'Fechar';
    botaoFechar.onclick = function() {
        document.getElementById('janela').remove();
    }

    areaAcoes.appendChild(botaoConfirmar);
    areaAcoes.appendChild(botaoLimpar);
    areaAcoes.appendChild(botaoFechar);

    divJanela.appendChild(areaAcoes);

    document.body.appendChild(divJanela);
    
//    const janela = document.getElementById('janela');
    const janela = divJanela;
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
    
    return divJanela;
    
};

function montaConsulta(dados) {
    const janela = document.getElementById('janela');
    const content = janela.getElementsByClassName('content')[0];
    let html = '<table>'
    dados.forEach(function(campo, idx) {
        if (idx == 0) {
            html += '<tr>';
            for (let key in campo) {
                html += `<th>${key}</th>`;
            }
            html += '</tr>';
        }
        html += '<tr>';
        for (let key in campo) {
            html += `<td>${campo[key]}</td>`;
        }
        html += '</tr>';
    });
    html += '</table>'
    content.innerHTML = html;
}

const montaManutencao = function(campos) {
    const janela = document.getElementById('janela');
    const content = janela.getElementsByClassName('content')[0];
    let html = '<table>'
    campos.forEach(function(campo) {
        let input = '';
        switch (campo.tipo) {
            case 'text':
                input = `<input name="${campo.nome}" type="text">`;
        }
        html += `<tr><td>${campo.titulo}:</td><td>${input}</td></tr>`
    });
    html += '</table>'
    content.innerHTML = html;
};

const confirma_submit = function() {
    const oRotina = document.getElementById('rotina');
    const values = {};
    document.getElementById('janela').getElementsByClassName('content')[0].querySelectorAll('*').forEach(function(el) {
        if (el.tagName == 'INPUT') {
            values[el.name] = el.value;
        }
    });
    
    loadAjax({
        rotina: oRotina.attributes['rotina'].value,
        acao: oRotina.attributes['acao'].value,
        processo: 'processaDados',
        parametro: {dados: values},
        completo: function() {
            
        }
    });
};

loadAjax = function(options) {
    const formData = new URLSearchParams();
    options.parametro = {rotina: options.rotina, acao: options.acao, ...options.parametro};
    formData.append('rotina', options.rotina);
    formData.append('acao', options.acao);
    formData.append('processo', options.processo);
    formData.append('parametro', JSON.stringify(options.parametro));
    formData.append('chave', options.chave);
    const busca = fetch('api/call_controller.php', {
        method: options.method || 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded'
        },
        body: formData
    });
    busca.then(response => {
        if (!response.ok) {
            options.exception && options.exception.call();
        }
        return response.json();
    })
    .then(function(response) {
        if (response.status == 'error') {
            alert(response.message+response.stack);
        } else {
            options.completo && options.completo.call(null, response);
        }
    }).catch (function(err) {
        alert(err.message);
    })
;
}

TelaPadrao = function() {
    
    this.limpa = function() {
        
    }
    
};