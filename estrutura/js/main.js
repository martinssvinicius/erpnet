const imgPreload = new Image();
imgPreload.src = '/imagens/imagem_temas_padrao_large_loading.gif';

function bloqueiaJanela(janela) {
    if (!janela) {
        janela = document.body;
    }
    
    const divBloq = document.createElement('div');
    divBloq.id = 'bloqueiaJanela';
    divBloq.style.backgroundColor = 'rgba(0, 0, 0, 0.2)';
    divBloq.style.height = '100%';
    divBloq.style.zIndex = '99999';
    
    const img = document.createElement('img');
    img.src = '/imagens/imagem_temas_padrao_large_loading.gif';
    img.style.position = 'fixed';
    img.style.top = '50%';
    img.style.left = '50%';
    img.style.zIndex = '999999';
    
    divBloq.appendChild(img);
    janela.appendChild(divBloq);
}

function desbloqueiaJanela(janela) {
    if (!janela) {
        janela = document;
    }
    janela.querySelector('#bloqueiaJanela')?.remove();
}

function abre_nova_janela(oChave, oParametros, oLink, oDados) {
    
    bloqueiaJanela();
    
    loadAjax({
        rotina: oLink.rotina,
        acao: oLink.acao,
        completo: function(res) {
            
            const oJanela = new Janela({
                titulo: res.titulo,
                rotina: oLink.rotina,
                acao: oLink.acao
            });
            
            if (res.tipo == 1) {
                montaConsulta(res, oLink.rotina, oLink.acao);
            }
            if (res.tipo == 2) {
                montaManutencao(res.campos, oLink.rotina, oLink.acao);
            }

            desbloqueiaJanela();
            
        },
        exception: function(res) {
            desbloqueiaJanela();
        }
    });
}

var Janela = function(opt) {
    const divJanela = document.createElement('div');
    divJanela.className = 'janela';
    divJanela.id = `janela_${opt.rotina}_${opt.acao}`;
    divJanela.setAttribute('rotina', opt.rotina);
    divJanela.setAttribute('acao', opt.acao);

    const header = document.createElement('header');
    header.textContent = opt.titulo;
    divJanela.appendChild(header);

    const areaFiltros = document.createElement('div');
    areaFiltros.className = 'areafiltros';
    areaFiltros.id = 'areafiltros';
    divJanela.appendChild(areaFiltros);

    const acoes = document.createElement('div');
    acoes.className = 'acoesConsulta';
    acoes.id = 'acoes_consulta';
    divJanela.appendChild(acoes);

    const divContent = document.createElement('div');
    divContent.className = 'content';
    divJanela.appendChild(divContent);

    const areaAcoes = document.createElement('div');
    areaAcoes.className = 'acoes';
    areaAcoes.id = 'area_acoes';
    divJanela.appendChild(areaAcoes);

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
        this.parentElement.parentElement.remove();
        
    }

    areaAcoes.appendChild(botaoConfirmar);
    areaAcoes.appendChild(botaoLimpar);
    areaAcoes.appendChild(botaoFechar);

    divJanela.appendChild(areaAcoes);

    document.body.appendChild(divJanela);
    
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

    const fn = () => {
        zIndexAtual++;
        janela.style.zIndex = zIndexAtual;
    };
    janela.addEventListener('mousedown', fn);
    fn();
    return divJanela;
    
};

function montaConsulta(data, rotina, acao) {
    const dados = data.dados;
    const janela = document.getElementById(`janela_${rotina}_${acao}`);
    const content = janela.getElementsByClassName('content')[0];
    const areaFiltros = janela.getElementsByClassName('areafiltros')[0];
    const areaAcoes = janela.getElementsByClassName('acoesConsulta')[0];
    
    areaFiltros.innerHTML = '<div><a href="#" onclick="atualizaConsulta()">Consultar</a></div>';
    let html = '<ul>';
    let htmlAcoes = '<ul>';
    data.acoes.forEach(function(acao) {
        if (!acao.titulo) {
            switch (acao.acao) {
                case 101:
                    acao.titulo = 'Consultar';
                    break;
                case 102:
                    acao.titulo = 'Incluir';
                    break;
                case 103:
                    acao.titulo = 'Alterar';
                    break;
                case 104:
                    acao.titulo = 'Excluir';
                    break;
                case 105:
                    acao.titulo = 'Visualizar';
                    break;
            }
        }
        htmlAcoes += `<li><a href="#" onclick="abre_nova_janela({}, {}, 
            {rotina:${acao.rotina}, acao:${acao.acao}}
        )">${acao.titulo}</a></li>`;
//        html += `<li><a>${acao.titulo}</a></li>`
    });
    htmlAcoes += '</ul>'
    areaAcoes.innerHTML = htmlAcoes;
    html = '<table>';
    dados.forEach(function(campo, idx) {
        if (idx == 0) {
            html += '<tr>';
            html += `<td></td>`;
            for (let key in campo) {
                html += `<th>${key}</th>`;
            }
            html += '</tr>';
        }
        html += '<tr>';
        const chave = campo['turcodigo'];
        html += `<td><input type="checkbox" chave="${chave}"></td>`;
        for (let key in campo) {
            html += `<td>${campo[key]}</td>`;
        }
        html += '</tr>';
    });
    html += '</table>'
    content.innerHTML = html;
}

const montaManutencao = function(campos, rotina, acao) {
    const janela = document.getElementById(`janela_${rotina}_${acao}`);
    const content = janela.getElementsByClassName('content')[0];
    let html = '<table>'
    campos.forEach(function(campo) {
        let input = '';
        switch (campo.tipo) {
            case 'serial':
                input = `<input name="${campo.nome}" type="number" disabled>`;
                break;
            case 'number':
                input = `<input name="${campo.nome}" type="number">`;
                break;
            case 'text':
                input = `<input name="${campo.nome}" type="text">`;
                break;
            case 'file':
                input = `<input name="${campo.nome}" type="file">`;
                break;
            case 'lista':
                input = `<select name="${campo.nome}" ></select>`;
                break;
        }
        html += `<tr><td>${campo.titulo}:</td><td>${input}</td></tr>`
    });
    html += '</table>'
    content.innerHTML = html;
};

const confirma_submit = function() {
    const rotina = event.target.parentElement.parentElement.getAttribute('rotina');
    const acao = event.target.parentElement.parentElement.getAttribute('acao');
    const values = {};
    const janela = document.getElementById(`janela_${rotina}_${acao}`);
    const files = [];
    janela.getElementsByClassName('content')[0].querySelectorAll('*').forEach(function(el) {
        if (el.type == 'file') {
//            files[el.name] = el.files[0];
            files.push({name: el.name, file: el.files[0]});
        } else if (el.tagName == 'INPUT') {
            values[el.name] = el.value;
        }
    });
    
    bloqueiaJanela(janela);
    
    loadAjax({
        rotina: rotina,
        acao: acao,
        processo: 'processaDados',
        parametro: {dados: values, files: files},
        completo: function() {
            desbloqueiaJanela(janela);
        },
        exception: function() {
            desbloqueiaJanela(janela);
        }
    });
};

loadAjax = function(options) {
//    const formData = new URLSearchParams();
    const formData = new FormData();
    options.parametro = {rotina: options.rotina, acao: options.acao, ...options.parametro};
    formData.append('rotina', options.rotina);
    formData.append('acao', options.acao);
    formData.append('processo', options.processo);
    formData.append('parametro', JSON.stringify(options.parametro));
    formData.append('chave', options.chave);
    options.parametro.files?.forEach(function(file) {
        formData.append(file.name, file.file);
    });
    const busca = fetch('/api/call_controller.php', {
        method: options.method || 'POST',
//        headers: {
//            'Content-Type': 'application/x-www-form-urlencoded'
//        },
        body: formData
    });
    busca.then(response => {
        if (!response.ok) {
            options.exception && options.exception.call();
        }
//        return response.text();
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
    });
}

TelaPadrao = function() {
    
    this.limpa = function() {
        
    }
    
};

click_janela = function() {
    
}

let zIndexAtual = 0;

// document.querySelectorAll('.janela').forEach(janela => {
//   janela.addEventListener('mousedown', () => {
//     zIndexAtual++;
//     janela.style.zIndex = zIndexAtual;
//   });
// });

function click_acao() {
    
}

function processa_dados_oculto() {
    
}

function Consulta() {
    
    this.atualiza = function() {
        
    }
    
}

function atualizaConsulta() {
    const el = event.target;
    const janela = el.parentElement.parentElement.parentElement;
    const rotina = janela.getAttribute('rotina');
    const acao = janela.getAttribute('acao');
    
    bloqueiaJanela(janela);
    
    loadAjax({
        rotina: rotina,
        acao: acao,
        completo: function(res) {
            montaConsulta(res, rotina, acao);
            desbloqueiaJanela(janela);
        }
    });
    
}

