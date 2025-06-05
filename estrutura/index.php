<?php

require_once './est_class_autoloader.inc';



?>

<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8">
        <title>ERP.Net</title>
        <title>title</title>
        <link rel="stylesheet" href="style/main.css"/>
    </head>
    <body>
        <header>
            <div class="menu">
                <ul>
                    <?php
                        $aMod = Conexao::getConexao()->query('select * from webbased.tbmodulo')->fetchAll(PDO::FETCH_ASSOC);
                        foreach ($aMod as $oMod) {
                            echo "<li>";
                            echo "<a href=\"#\">{$oMod['moddescricao']}</a>";
                            $aFormMod = Conexao::getConexao()->query("select * from webbased.tbformmod "
                                    . "where modcodigo = {$oMod['modcodigo']}")->fetchAll(PDO::FETCH_ASSOC);
                            echo "<ul class=\"submenu\">";
                            foreach ($aFormMod as $idx => $oFormMod) {
                            echo "<li><a id=\"rotina\" href=\"#\" rotina=\"{$oFormMod['rotcodigo']}\" "
                                    . "acao=\"{$oFormMod['acacodigo']}\" "
                                    . "onclick=\"abre_nova_janela({}, {}, {rotina:{$oFormMod['rotcodigo']}, acao:{$oFormMod['acacodigo']}})\""
                                    . ">{$oFormMod['fmotitulo']}</a></li>
                                ";
                            }
                            echo "</ul>";
                            echo "</li>";
                        }
                    ?>
                </ul>
            </div>
        </header>
        <script src="https://code.jquery.com/jquery-3.7.1.min.js"></script>
        <script src="comportamento/main.js"></script>
        <script src="comportamento/tela_padrao.js"></script>
    </body>
</html>
