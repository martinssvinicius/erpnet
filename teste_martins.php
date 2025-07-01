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

//readMyFileMarc();
function readMyFileMarc() {
    ini_set("default_charset", "UTF-8");
//    ini_set("default_charset", "ISO-8859-1");
//    ini_set("default_charset", "Windows-1252");
//    $caminhoArquivo = '../temp/teste1.mrc';
//    $caminhoArquivo = '../temp/_el_hombre_mediocre;_ensa_iso.txt';
//    $caminhoArquivo = '../temp/records (1).mrc';
//    $caminhoArquivo = '../temp/110_1_zipped.mrc';
//    $caminhoArquivo = '../temp/110_1_7z.mrc';
    $caminhoArquivo = '../temp/1101_1.mrc';
    $content = file_get_contents($caminhoArquivo);
                        'OrganizacÌ§aÌ\u0083o das NacÌ§oÌ\u0083es Unidas';
//    mb_convert_encoding('OrganizacÌ§aÌ?o das NacÌ§oÌ?es Unidas', 'ISO-8859-1', 'UTF-8');
//    mb_detect_encoding('OrganizacÌ§aÌ?o das NacÌ§oÌ?es Unidas')
    
    echo ini_get("default_charset");
    $dadosAutor = [];

//    require_once __DIR__ . '/estrutura/libs/File_MARC-1.4.1/File/MARC.php';
    
    $marc = new \Ebi\View\ViewFileMarc($caminhoArquivo);

    while ($record = $marc->next()) {
        $campo100 = $record->getField('110'); // Autor principal
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

function testeSeila() {
//        $this->testeSoapServer();
    return response()->file(public_path('teste.html'));
}
    
function testeSoapServer() {
    $client = new \SoapClient("http://localhost/calculadora.wsdl");
    $response = $client->__soapCall("somar", [["a" => 10, "b" => 20]]);
    echo "Resultado: " . $response->resultado;
}

function testeCUrlPost() {
    $data = [
        "title" => "Teste",
        "body" => "Conteúdo aqui",
        "userId" => 1
    ];

    $ch = curl_init("https://jsonplaceholder.typicode.com/posts");
    curl_setopt($ch, CURLOPT_POST, true);
    curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode($data));
    curl_setopt($ch, CURLOPT_HTTPHEADER, [
        'Content-Type: application/json'
    ]);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);

    $response = curl_exec($ch);
    curl_close($ch);

    $result = json_decode($response, true);
    echo "ID criado: " . $result["id"];
}

function testeCUrlGet() {
    $ch = curl_init("https://jsonplaceholder.typicode.com/posts/1");
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);

    $response = curl_exec($ch);
    curl_close($ch);

    $data = json_decode($response, true);
    echo "Título: " . $data["title"];
}

function testeApiRest() {
    $url = "https://jsonplaceholder.typicode.com/posts/1";
    $response = file_get_contents($url);

    $data = json_decode($response, true);
    echo "Título: " . $data["title"];
}

function testeMicrotime() {
    $ini = microtime(true);
    foreach ($this->returnYield() as $el) {
//        foreach ($this->returnYieldArray() as $el) {
        echo $el;
    }
    echo '<br>'.(microtime(true) - $ini);
}

function testeHintEdu() {
    $dados = [
        'label1' => 'valor1',
        'label2' => 'valor2',
        'label3' => 'valor3',
    ];

    echo '<table>TITULO GERAL';
    foreach ($dados as $label => $valor) {
        echo "<tr style=\"display:flex !important;\"><td><b> $label: </b> $valor</td></tr>";
    }
    echo '</table>';
}

function testeApiSoap() {
    $client = new \SoapClient('http://www.dneonline.com/calculator.asmx?WSDL');
    $response = $client->__soapCall('Add', [[
        'intA' => 10,
        'intB' => 20
    ]]);
}

function arrayToNode() {
//        $result = \App\Http\Utils::arrayToList([1,2,3,4,5]);
//        print_r($result);
}

function nodeListProblem() {
    $lists = [
        new ListNode(1, new ListNode(4, new ListNode(5))),
        new ListNode(1, new ListNode(3, new ListNode(4))),
        new ListNode(2, new ListNode(6)),
    ];

    $listNodeToArray = function(ListNode $ListNode) use (&$listNodeToArray, &$result) {
        foreach ($ListNode as $List) {
            if ($List instanceof ListNode) {
                $listNodeToArray($List);
            } else if (!is_null($List)) {
                $result[] = $List;
            }
        }
    };
    $newList = [];
    foreach ($lists as $list) {
        if (!($list instanceof ListNode)) {
            continue;
        }
        $result = [];
        $listNodeToArray($list);
        $newList = array_merge($newList,$result);
    }
    rsort($newList);
    $newLisNode = null;
    foreach ($newList as $index => $val) {
        $newLisNode = new ListNode($val, $newLisNode);
    }
    return $newLisNode;
}

function getYield() {
//        foreach () ;
}

function returnYieldArray() {
    $a = [];
    for ($i = 1; $i < 1000000; $i++) {
        $a[] = $i;
    }
    return $a;
}

function returnYield() {
    for ($i = 1; $i < 1000000; $i++) {
        yield $i;
    }
}

//processaPhpOffice();
function processaPhpOffice() {
//    require_once 'C:\vinicius.martins\Repositório\erpnet\estrutura\libs\phpoffice\phpspreadsheet\src\PhpSpreadsheet\IOFactory.php'; 
    
   $aFile = file_get_contents('../temp/layout_de_importacao_e_exportacao_2025.xlsx');
//    $oSpreadsheet = \PhpOffice\PhpSpreadsheet\IOFactory::load($aFile['tmp_name']);
    $oSpreadsheet = \PhpOffice\PhpSpreadsheet\IOFactory::load('../temp/layout_de_importacao_e_exportacao_2025.xlsx');
//        $sheet = $spreadsheet->getActiveSheet();
    $aGrupo = [
        '10',
        '20',
        '30',
        '40',
    ];
    foreach ($aGrupo as $sGrupo) {
        $oWorkSheet = $oSpreadsheet->getSheetByName($sGrupo);
        foreach ($oWorkSheet->getRowIterator() as $oRow) {
            $iLinha = $oRow->getRowIndex();
            $sCodigo = $oWorkSheet->getCell("A{$iLinha}")->getValue();
            if (is_int($sCodigo)) {
                $sNomeCampo = $oWorkSheet->getCell("B{$iLinha}")->getValue();
                $oContentColumnC = $oWorkSheet->getCell("C{$iLinha}")->getValue();
                $sNomeFormatado = str_replace(' ', '', ucwords(str_replace('_', ' ', $sNomeCampo)));
                if (isset($aIntervaloCodigo) && $sCodigo >= $aIntervaloCodigo[0] && $sCodigo <= $aIntervaloCodigo[1]) {
                    $sNomeFormatado = $sNomeAgrupadorFormatado . $sNomeFormatado;
                }
                if ($oContentColumnC instanceof \PhpOffice\PhpSpreadsheet\RichText\RichText) {
                    $sInfoBasica = $oContentColumnC->getPlainText();
                    $sInfoBasica = preg_replace('/Tamanho máximo:|Tamanho fixo:|Formato:|Obrigatório:/', '', $sInfoBasica);
                    $aInfoBasica = explode(ENTER, $sInfoBasica);
                    $aInfoBasica = array_map(function($sInfo) {
                        return trim($sInfo);
                    }, $aInfoBasica);
                    if (!empty($aInfoBasica)) {
                        $tamanho = $aInfoBasica[0];
                        $tamFixo = $aInfoBasica[1] == 'Sim' ? 1 : 0;
                        $formato = $aInfoBasica[2];
                        $obrigatorio = $aInfoBasica[3];
                    }
                }
                \Illuminate\Support\Facades\DB::statement("insert into public.tblayout values ("
                        . "$sCodigo, "
                        . "'$sGrupo',"
                        . "'$sNomeFormatado',"
                        . "'$sNomeCampo',"
                        . "$tamanho,"
                        . "$tamFixo,"
                        . "'$formato',"
                        . "'$obrigatorio'"
                        . ")");
            } else if (str_contains($sCodigo, ' a ')) {
                $aIntervaloCodigo = explode(' a ', $sCodigo);
                $sTituloAgrupador = $oWorkSheet->getCell("B{$iLinha}")->getValue();
                $sNomeAgrupadorFormatado = str_replace(' ', '', ucwords(str_replace('_', ' ', $sTituloAgrupador)));
            }
        }
    }
}

class ListNode {
    
    public $val = 0;
    public $next = null;
    function __construct($val = 0, $next = null) {
        $this->val = $val;
        $this->next = $next;
    }
    
}

define('ENTER', '
');

//teste2906();
function teste2906() {
    echo (true xor false);
//    echo 'teste';
}

//testeApiTranslate();
function testeApiTranslate() {
// Configurações da API
$apiUrl = 'https://libretranslate.de/translate';
$sourceText = 'Hello, how are you?';
$sourceLang = 'en'; // Código do idioma de origem (inglês)
$targetLang = 'pt'; // Código do idioma de destino (português)

// Dados da requisição
$postData = [
    'q' => $sourceText,
    'source' => $sourceLang,
    'target' => $targetLang,
    'format' => 'text'
];

// Inicializa o cURL
$ch = curl_init($apiUrl);

// Configura as opções do cURL
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch, CURLOPT_POST, true);
curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode($postData));
curl_setopt($ch, CURLOPT_HTTPHEADER, [
    'Content-Type: application/json',
]);

// Executa a requisição e obtém a resposta
$response = curl_exec($ch);

// Verifica erros
if (curl_errno($ch)) {
    echo 'Erro no cURL: ' . curl_error($ch);
} else {
    $decodedResponse = json_decode($response, true);
    if (isset($decodedResponse['translatedText'])) {
        echo "Texto original: " . $sourceText . "\n";
        echo "Tradução: " . $decodedResponse['translatedText'] . "\n";
    } else {
        echo "Erro na tradução: " . $response . "\n";
    }
}

// Fecha a sessão cURL
curl_close($ch);
}

//charsetTests();
function charsetTests() {
//    ini_set("default_charset", "UTF-8");
//    ini_set("default_charset", "ISO-8859-1");
    ini_set("default_charset", "Windows-1252");
//    $caminhoArquivo = '../temp/teste1.mrc';
//    $caminhoArquivo = '../temp/_el_hombre_mediocre;_ensa_iso.txt';
//    $caminhoArquivo = '../temp/records (1).mrc';
//    $caminhoArquivo = '../temp/110_1_zipped.mrc';
//    $caminhoArquivo = '../temp/110_1_7z.mrc';
    $caminhoArquivo = '../temp/1101_1.mrc';
    $content = file_get_contents($caminhoArquivo);
    echo $content;
//                        'OrganizacÌ§aÌ\u0083o das NacÌ§oÌ\u0083es Unidas';
//    mb_convert_encoding('OrganizacÌ§aÌ?o das NacÌ§oÌ?es Unidas', 'ISO-8859-1', 'UTF-8');
//    mb_detect_encoding('OrganizacÌ§aÌ?o das NacÌ§oÌ?es Unidas')
    
//    echo ini_get("default_charset");
    
    echo '<br>';
    
    $decoded = mb_convert_encoding($content, 'UTF-8', 'Windows-1252');
    echo $decoded;
    
    echo '<br>';
    
    $decoded = mb_convert_encoding($decoded, 'UTF-8', 'UTF-8');
    echo $decoded;
    
    echo '<br>';
    echo '<br>';
    
    $bytes = file_get_contents($caminhoArquivo);

    // Converte de UTF-8 para string correta (se o arquivo for UTF-8)
    $content = mb_convert_encoding($bytes, 'UTF-8', 'UTF-8'); 

    // Se ainda não funcionar, tente detectar a codificação:
    $encoding = mb_detect_encoding($bytes, ['UTF-8', 'Windows-1252', 'ISO-8859-1'], true);
    $content = mb_convert_encoding($bytes, 'UTF-8', $encoding);
    echo $content;
    
    echo '<br>';
    echo '<br>';
    
    // Abre o arquivo com um filtro para forçar UTF-8
    $handle = fopen($caminhoArquivo, 'r');
    stream_filter_append($handle, 'convert.iconv.UTF-8/UTF-8'); // Força UTF-8
    $content = stream_get_contents($handle);
    fclose($handle);
    
    echo '<br>';
    echo '<br>';
    
    $content = base64_encode(file_get_contents($caminhoArquivo));
    // Em outro script:
    $original = base64_decode($content); // Bytes puros, sem conversão maluca
    echo $original;
    
    echo '<br>';
    echo '<br>';
    
    $bytes = file_get_contents($caminhoArquivo);

    // Tenta detectar a codificação REAL do arquivo
    $encoding = mb_detect_encoding($bytes, [
        'UTF-8', 
        'Windows-1252', 
        'ISO-8859-1', 
        'ASCII',
        'UTF-16LE',
        'UTF-16BE'
    ], true);

    if (!$encoding) {
        // Se não detectar, força UTF-8 e remove BOM se existir
        $bytes = preg_replace('/^\xEF\xBB\xBF/', '', $bytes); // Remove BOM do UTF-8
        $encoding = 'UTF-8';
    }

    // Converte para UTF-8 (se não já for)
    $content = ($encoding === 'UTF-8') ? $bytes : mb_convert_encoding($bytes, 'UTF-8', $encoding);

    // Verifica se há caracteres inválidos (opcional)
    $content = mb_convert_encoding($content, 'UTF-8', 'UTF-8');

    echo $content; // Deve sair correto agora!
    
//    strtr($encoding, $caminhoArquivo, $to)
}

//charsetTests2();
function charsetTests2() {
    ini_set("default_charset", "Windows-1252");
    
    $caminhoArquivo = '../temp/1101_1.mrc';
    
    // Passo 1: Lê o arquivo como BINÁRIO
    $bytes = file_get_contents($caminhoArquivo);

    // Passo 2: Remove caracteres de controle MARC (opcional, se atrapalhar)
    $texto = preg_replace('/[\x00-\x1F\x7F]/', '', $bytes); // Remove ASCII não-printáveis

    // Passo 3: Converte apenas o conteúdo textual para UTF-8 (se estiver em Latin-1)
    $texto = mb_convert_encoding($texto, 'Windows-1252', 'UTF-8');

    // Passo 4: Processa campos MARC (exemplo: campo 100 = título)
    if (preg_match('/a([^]+)/', $texto, $matches)) {
        $titulo = $matches[1]; // "Organização das Nações Unidas"
        echo $titulo;
    }
    $titulo = $matches[1]; // "Organização das Nações Unidas"
    echo $titulo;
//    echo 'teste';
}

//charsetTests3();
function charsetTests3() {
//    ini_set("default_charset", "UTF-8");
    ini_set("default_charset", "Windows-1252");
//    $bytes = file_get_contents('../temp/1101_1.mrc');
//    echo $bytes;
//    $decoded = iconv('UTF-8', "Windows-1252//TRANSLIT//IGNORE", $bytes);
//    echo '<br>';
//    echo $decoded;
    
     // 1. Abre o arquivo como stream binário
    $handle = fopen('../temp/1101_1.mrc', 'rb');
    
    // 2. Adiciona um filtro de conversão para UTF-8 DURANTE a leitura
    stream_filter_append($handle, 'convert.iconv.UTF-8/UTF-8');
    
    // 3. Lê o conteúdo JÁ CONVERTIDO
    $conteudoUTF8 = stream_get_contents($handle);
    fclose($handle);
    echo $conteudoUTF8;
}

//charset4();
function charset4() {
    ini_set("default_charset", "Windows-1252");
    
//    $conteudo = file_get_contents('../temp/1101_1.mrc');
//
//    // Mesmo que PHP esteja em Windows-1252, os bytes ainda são os corretos
//    // Precisamos apenas garantir que sejam tratados como UTF-8
//
//    if (!mb_detect_encoding($conteudo, 'UTF-8', true)) {
//        // Provavelmente PHP interpretou errado ? forçamos a reinterpretação correta
//        $conteudo = mb_convert_encoding($conteudo, 'UTF-8', 'Windows-1252');
//    }
//
//    // Força UTF-8 para o navegador, sem usar ini_set
//    header("Content-Type: text/html; charset=UTF-8");
//
//    echo $conteudo;
    
    $conteudo = file_get_contents('../temp/1101_1.mrc');
    $conteudo = mb_convert_encoding($conteudo, 'UTF-8', 'UTF-8'); // "reforça" UTF-8

    header("Content-Type: text/html; charset=UTF-8");

    echo $conteudo;
}

testeCharsetBd();
function testeCharsetBd() {
    ini_set("default_charset", "Windows-1252");
    $conteudo = file_get_contents('../temp/1101_1.mrc');
    
//    $conteudoConvertido = mb_convert_encoding($conteudo, 'UTF-8', 'Windows-1252');
    
//    $query = new Query();
//    $query->set_sql("insert into charset_teste values ('$conteudoConvertido')");
//    $query->execute();
    echo $conteudo;
    echo '<br>';
    echo json_encode(['res' => $conteudo]);
    echo '<br>';
    ?>
    <script>
        const content = JSON.parse('{"res":"00264nz a2200097n 4500001000800000003000600008005001700014008003900031110006800070670002800138\u001e1000002\u001eBR-Bn\u001e20250627114200.0\u001e240101n||azannaabn||||||||||n|aaa|||||\u001e2 \u001faOrganizac\u0327a\u0303o das Nac\u0327o\u0303es Unidas.\u001fbConselho de Seguranc\u0327a\u001e \u001faResoluc\u0327o\u0303es oficiais\u001e\u001d"}');
        console.log(content);
    </script>
    <?php        
}

//$mapa_correcao = [
//    'Ã§' => 'ç',
//    'Ã£' => 'ã',
//    'Ã¡' => 'á',
//    'Ã³' => 'ó',
//    'Ã©' => 'é',
//    'Ãª' => 'ê',
//    'Ã ' => 'à'  // Espaço pode variar
//];