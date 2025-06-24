<?php

function writeFileMarc() {
    require_once __DIR__ . '/estrutura/libs/File_MARC-1.4.1/File/MARC.php';

    $record = new File_MARC_Record('245');

    file_put_contents(__DIR__.'/temp/teste1.txt', 'vini');
    file_put_contents('../temp/teste1.txt', 'vini');

    $record = new File_MARC_Record();

    // Adicionar campo 245 (título)
    $title = new File_MARC_Data_Field('245', [
        new File_MARC_Subfield('a', 'Dom Casmurro'),
        new File_MARC_Subfield('b', 'romance brasileiro')
    ], 0, 1);

    $record->appendField($title);

    // Salvar em arquivo
    $marc_data = $record->toRaw();
    file_put_contents('../temp/teste1.mrc', $marc_data, FILE_APPEND);

    echo 'teste';

    file_put_contents('/temp/livro.mrc', 'teste');

    // 2. Adicionar campos (exemplo: livro fictício)
    // Campo 245: Título (ind1=1, ind2=0)
    //$title = new File_MARC_Data_Field('245', [
    //    'ind1' => '1',
    //    'ind2' => '0'
    //]);
    //$title->appendSubfield(new File_MARC_Subfield('a', 'Aprendendo MARC21 com PHP'));
    //$title->appendSubfield(new File_MARC_Subfield('b', 'Guia prático para iniciantes'));
    //$record->appendField($title);
    //
    //// Campo 100: Autor (ind1=1, ind2= )
    //$author = new File_MARC_Data_Field('100', [
    //    'ind1' => '1',
    //    'ind2' => ' '
    //]);
    //$author->appendSubfield(new File_MARC_Subfield('a', 'Silva, João'));
    //$record->appendField($author);
    //
    //// Campo 260: Publicação (ind1= , ind2= )
    //$pub = new File_MARC_Data_Field('260', [
    //    'ind1' => ' ',
    //    'ind2' => ' '
    //]);
    //$pub->appendSubfield(new File_MARC_Subfield('a', 'São Paulo'));
    //$pub->appendSubfield(new File_MARC_Subfield('b', 'Editora PHP'));
    //$pub->appendSubfield(new File_MARC_Subfield('c', '2023'));
    //$record->appendField($pub);
    //
    //// Campo 650: Assunto (ind1= , ind2=0)
    //$subject = new File_MARC_Data_Field('650', [
    //    'ind1' => ' ',
    //    'ind2' => '0'
    //]);
    //$subject->appendSubfield(new File_MARC_Subfield('a', 'MARC21'));
    //$subject->appendSubfield(new File_MARC_Subfield('a', 'PHP'));
    //$record->appendField($subject);
    //
    //// 3. Exibir o registro em formato legível
    //echo "=== Registro MARC21 (Texto) ===\n";
    //echo $record;
    //
    //// 4. Exportar para MARC21 binário (para gravar em arquivo)
    //$marcBinary = $record->toRaw();
    //echo "\n=== Registro MARC21 (Binário) ===\n";
    //echo bin2hex($marcBinary);
    //
    //// 5. Salvar em um arquivo .mrc (opcional)
    //file_put_contents('livro.mrc', $marcBinary);
    //echo "\n\nArquivo 'livro.mrc' gerado com sucesso!";
}

//readFileMarc();
function readFileMarc() {
    require_once __DIR__ . '/estrutura/libs/File_MARC-1.4.1/File/MARC.php';
    
    $marcFile = new File_MARC('C:\Users\marti\Downloads\records.mrc');
    
    while ($record = $marcFile->next()) {
        
        $a = $record;
    }
    
}

class TesteMartins {
    
    public function echoTeste() {
        echo 'teste';
    }
    
    public function __destruct() {
        $a = 1;
    }
    
}

//echoTeste();
function echoTeste() {
    $class = new TesteMartins();
    $class->echoTeste();
//    unset($class);
}

//callApiGoogleBooksFileGetContents();
function callApiGoogleBooksFileGetContents() {
    $data = file_get_contents('https://www.googleapis.com/books/v1/volumes?q=isbn:9788575224038');
//    file_put_contents('../temp/isbn.txt', $data);
}

function callApiOpenLibrary() {
    $data = file_get_contents('https://openlibrary.org/api/books?bibkeys=ISBN:9788575224038&format=json&jscmd=data');
    
}

//callApiGoogleBooksCurl();
function callApiGoogleBooksCurl() {
    $url = 'https://www.googleapis.com/books/v1/volumes?q=isbn:9788575224038';
    $curl = curl_init($url);
    curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($curl, CURLOPT_TIMEOUT, 10);
    
//    curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, false);
    
    $response = curl_exec($curl);
    
    $httpCode = curl_getinfo($curl, CURLINFO_HTTP_CODE);

    curl_close($curl);

    if ($httpCode === 200) {
        $data = json_decode($response, true);
        
        $info = isset($data['items'][0]['volumeInfo']) ? $data['items'][0]['volumeInfo'] : null;
        if (!is_null($info)) {
            $oModelObra = new ModelObra();
            $oModelObra->setTitulo($info['title']);
            $oModelObra->setSubtitulo($info['subtitle']);
            $oModelObra->setIsbn($isbn);
            $oModelObra->setNumPagina($info['pageCount']);
            $oModelObra->setDataPublicacao($info['publishedDate']);
        }
        
        echo $data['items'][0]['volumeInfo']['title'];
    } else {
        echo "Erro: $httpCode";
    }
    
    file_put_contents('../temp/isbn_google_books_curl.txt', $response);
}

//fetch('https://www.googleapis.com/books/v1/volumes?q=isbn:9788575224038').then(function(res) {
//    return res.json()
//}).then(function(res) {
//    debugger
//})

//readIsbnFromFile();
function readIsbnFromFile() {
    $data = file_get_contents('C:\vinicius.martins\Repositório\erpnet\temp\isbn9788575224038.json');
    $data = json_decode($data, true);
}

//print_r(lerMARC('../temp/teste1.mrc'));
function lerMARC($arquivo) {
    $conteudo = file_get_contents($arquivo);
    $registros = explode("\x1D", $conteudo); // \x1D = fim de registro MARC

    $dados = [];

    foreach ($registros as $registro) {
        if (trim($registro) === '') continue;

        $leader = substr($registro, 0, 24); // Leader = 24 bytes
        $baseAddress = intval(substr($leader, 12, 5)); // Início dos dados de campo

        $directory = substr($registro, 24, $baseAddress - 25); // Directory termina em \x1E

        $campos = [];
        for ($i = 0; $i < strlen($directory); $i += 12) {
            $tag = substr($directory, $i, 3);
            $length = intval(substr($directory, $i + 3, 4));
            $offset = intval(substr($directory, $i + 7, 5));
            $conteudoCampo = substr($registro, $baseAddress + $offset, $length - 1); // -1 para remover o \x1E
            $campos[$tag][] = $conteudoCampo;
        }

        // Extrair subcampos dos campos desejados
        $extrairSubcampos = function($campo) {
            $subcampos = explode("\x1F", $campo);
            $resultado = [];
            foreach ($subcampos as $s) {
                if ($s === '') continue;
                $codigo = substr($s, 0, 1);
                $valor = substr($s, 1);
                $resultado[$codigo] = $valor;
            }
            return $resultado;
        };

        // Pegando alguns campos padrão
        if (!empty($campos['245'])) {
            $sub = $extrairSubcampos($campos['245'][0]);
            $dados['titulo'] = ($sub['a'] ?? '') . (isset($sub['b']) ? ": {$sub['b']}" : '');
        }

        if (!empty($campos['100'])) {
            $sub = $extrairSubcampos($campos['100'][0]);
            $dados['autor'] = $sub['a'] ?? '';
        }

        if (!empty($campos['020'])) {
            $sub = $extrairSubcampos($campos['020'][0]);
            $dados['isbn'] = $sub['a'] ?? '';
        }

        if (!empty($campos['260'])) {
            $sub = $extrairSubcampos($campos['260'][0]);
            $dados['editora'] = $sub['b'] ?? '';
            $dados['ano'] = $sub['c'] ?? '';
        }
    }

    return $dados;
}

require 'estrutura/vendor/autoload.php';
use Elastic\Elasticsearch\ClientBuilder;
//testeElasticSearchIndex();
function testeElasticSearchIndex() {
    $client = ClientBuilder::create()
        ->setHosts(['localhost:9200'])
        ->build();
    
    $params = [
        'index' => 'livros',
        'id' => '1',
        'body' => [
            'titulo' => 'Dom Casmurro',
            'autor' => 'Machado de Assis',
            'ano'   => 1899
        ]
    ];
    $response = $client->index($params);
//    print_r($response);
    
}

//testeElasticSearchSearch();
function testeElasticSearchSearch() {
    
    $client = ClientBuilder::create()
        ->setHosts(['localhost:9200'])
        ->build();
    
    $params = [
        'index' => 'livros',
        'body'  => [
            'query' => [
                'match' => [
                    'autor' => 'Machado'
                ]
            ]
        ]
    ];
    
    $response = $client->search($params);
//    print_r($response);
    
    foreach ($response['hits']['hits'] as $hit) {
        echo $hit['_source']['titulo'] . " - " . $hit['_source']['autor'] . "<br>";
    }

    
}

//lerMARCAutor();
function lerMARCAutor() {
//    $arquivo = '../temp/teste1.mrc';
    $arquivo = '../temp/records (1).mrc';
    $conteudo = file_get_contents($arquivo);
    $registros = explode("\x1D", $conteudo); // separador de registro MARC

    $dadosAutores = [];

    foreach ($registros as $registro) {
        if (empty($registro)) continue;

        $autor = '';
        $sobrenome = '';
        $nome = '';
        $tipoAutor = 'Autor';
        $cutter = '';
        $referencia = trim($registro);

        // extrair campo 100 (autor principal) ou 700 (autor adicional)
        if (preg_match('/100..\\$a([^\\$]+)(\\$e([^\\$]+))?/u', $registro, $matches) ||
            preg_match('/700..\\$a([^\\$]+)(\\$e([^\\$]+))?/u', $registro, $matches)) {

            $nomeCompleto = trim($matches[1]);
            $tipoAutor = isset($matches[3]) ? trim($matches[3]) : 'Autor';

            $partes = explode(',', $nomeCompleto);
            $sobrenome = trim($partes[0] ?? '');
            $nome = trim($partes[1] ?? '');
        }

        // extrair campo 090 ou 050 (para código Cutter)
        if (preg_match('/090..\\$b([^\\$]+)/u', $registro, $matches) ||
            preg_match('/050..\\$b([^\\$]+)/u', $registro, $matches)) {
            $cutter = trim($matches[1]);
        }

        if ($nome || $sobrenome) {
            $dadosAutores[] = [
                'nome'       => $nome,
                'sobrenome'  => $sobrenome,
                'tipo'       => $tipoAutor,
                'cutter'     => $cutter,
                'referencia' => $referencia,
            ];
        }
    }

    return $dadosAutores;
}

function lerMarcAutorLib() {
    
}

//extrairAutorDeMARC();
function extrairAutorDeMARC() {
//    $caminhoArquivo = '../temp/teste1.mrc';
//    $caminhoArquivo = '../temp/_el_hombre_mediocre;_ensa_iso.txt';
    $caminhoArquivo = '../temp/records (1).mrc';
    $dadosAutor = [];

    require_once __DIR__ . '/estrutura/libs/File_MARC-1.4.1/File/MARC.php';
    
    $marc = new File_MARC($caminhoArquivo);

    while ($record = $marc->next()) {
        $campo100 = $record->getField('100'); // Autor principal
        $campo700 = $record->getField('700'); // Autor adicional

        $autor = $campo100 ?: $campo700;

        if ($autor) {
            $suba = $autor->getSubfield('a'); // Nome completo
            $sube = $autor->getSubfield('e'); // Tipo de autor (ex: organizador, tradutor)
            $subc = $autor->getSubfield('c'); // Informações complementares (ex: título, cargo)

            $nomeCompleto = trim($suba ? $suba->getData() : '');
            $tipoAutor    = trim($sube ? $sube->getData() : '');
            $complemento  = trim($subc ? $subc->getData() : '');

            // Quebra em nome e sobrenome (pode ser adaptado conforme formato)
            $partes = explode(',', $nomeCompleto);
            $sobrenome = trim($partes[0] ?? '');
            $nome      = trim($partes[1] ?? '');

            // Cutter (se presente no campo 090 subcampo b, ou campo 050 subcampo b)
            $cutter = '';
            $campo090 = $record->getField('090');
            if ($campo090) {
                $subb = $campo090->getSubfield('b');
                $cutter = $subb ? trim($subb->getData()) : '';
            }

            // Referência bibliográfica básica
            $referencia = $record->toRaw();

            $dadosAutor[] = [
                'nome'       => $nome,
                'sobrenome'  => $sobrenome,
                'tipo'       => $tipoAutor ?: 'Autor',
                'cutter'     => $cutter,
                'referencia' => $referencia,
            ];
        }
    }

    return $dadosAutor;
}

function myMarcReader() {
    
    $caminhoArquivo = '../temp/records (1).mrc';
    
    $this->xmlwriter = new XMLWriter();
    $this->xmlwriter->openMemory();
    $this->xmlwriter->startDocument('1.0', 'UTF-8');
    
    $this->source = fopen($caminhoArquivo, 'rb');
    
    $record = stream_get_line($this->source, 99999, "\x1D");
    $record = preg_replace('/^[\\x0a\\x0d\\x00]+/', "", $record);
    $record .= "\x1D";
    
    
}

//lerMRCBinario();
function lerMRCBinario() {
    $arquivo = '../temp/records (1).mrc';
    $conteudo = file_get_contents($arquivo);
    $registros = explode("\x1D", $conteudo); // separador MARC de registros

    $dados = [];

    foreach ($registros as $registro) {
        if (strlen($registro) < 24) continue;

        $tamanhoRegistro = (int)substr($registro, 0, 5);
        $baseEnd = (int)substr($registro, 12, 5);
        $diretorio = substr($registro, 24, $baseEnd - 24);
        $dadosCampos = substr($registro, $baseEnd);

        $campos = [];

        for ($i = 0; $i < strlen($diretorio); $i += 12) {
            $tag = substr($diretorio, $i, 3);
            $length = (int)substr($diretorio, $i + 3, 4);
            $start = (int)substr($diretorio, $i + 7, 5);
            $valor = substr($dadosCampos, $start, $length - 1); // remove terminador

            $campos[$tag][] = $valor;
        }

        // campo 100 (autor principal)
        $campo100 = $campos['100'][0] ?? '';
        $autor = '';
        if ($campo100) {
            $subcampos = explode("\x1F", $campo100); // separador de subcampo
            foreach ($subcampos as $sub) {
                if (str_starts_with($sub, 'a')) {
                    $autor = trim(substr($sub, 1));
                }
            }
        }

        $dados[] = [
            'autor' => $autor,
            'raw'   => $registro,
        ];
    }

    return $dados;
}

readMyFileMarc();
function readMyFileMarc() {
//    $caminhoArquivo = '../temp/teste1.mrc';
//    $caminhoArquivo = '../temp/_el_hombre_mediocre;_ensa_iso.txt';
    $caminhoArquivo = '../temp/records (1).mrc';
    $dadosAutor = [];

//    require_once __DIR__ . '/estrutura/libs/File_MARC-1.4.1/File/MARC.php';
    
    $marc = new \Ebi\View\ViewFileMarc($caminhoArquivo);

    while ($record = $marc->next()) {
        $campo100 = $record->getField('100'); // Autor principal
        $campo700 = $record->getField('700'); // Autor adicional

        $autor = $campo100 ?: $campo700;

        if ($autor) {
            $suba = $autor->getSubfield('a'); // Nome completo
            $sube = $autor->getSubfield('e'); // Tipo de autor (ex: organizador, tradutor)
            $subc = $autor->getSubfield('c'); // Informações complementares (ex: título, cargo)

            $nomeCompleto = trim($suba ? $suba->getData() : '');
            $tipoAutor    = trim($sube ? $sube->getData() : '');
            $complemento  = trim($subc ? $subc->getData() : '');

            // Quebra em nome e sobrenome (pode ser adaptado conforme formato)
            $partes = explode(',', $nomeCompleto);
            $sobrenome = trim($partes[0] ?? '');
            $nome      = trim($partes[1] ?? '');

            // Cutter (se presente no campo 090 subcampo b, ou campo 050 subcampo b)
            $cutter = '';
            $campo090 = $record->getField('090');
            if ($campo090) {
                $subb = $campo090->getSubfield('b');
                $cutter = $subb ? trim($subb->getData()) : '';
            }

            // Referência bibliográfica básica
            $referencia = $record->toRaw();

            $dadosAutor[] = [
                'nome'       => $nome,
                'sobrenome'  => $sobrenome,
                'tipo'       => $tipoAutor ?: 'Autor',
                'cutter'     => $cutter,
                'referencia' => $referencia,
            ];
        }
    }

//    return $dadosAutor;
    print_r($dadosAutor);
}