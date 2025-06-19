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

readFileMarc();
function readFileMarc() {
    require_once __DIR__ . '/estrutura/libs/File_MARC-1.4.1/File/MARC.php';
    
    $marcFile = new File_MARC('C:\Users\marti\Downloads\records.mrc');
    
    while ($record = $marcFile->next()) {
        
        $a = $record;
    }
    
}