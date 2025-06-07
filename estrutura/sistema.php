<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8">
        <title>ERP.Net</title>
        <title>title</title>
        <link rel="stylesheet" href="/style/main.css"/>
    </head>
    <body>
        <aside>
            <nav>
                <div class="sidebar">
                    <ul>
                        <?php
                            $aCon = Conexao::getConexao()->query('select * from webbased.tbconjunto order by 1')->fetchAll(PDO::FETCH_ASSOC);
                            foreach ($aCon as $oCon) {
                                echo "<li>";
                                echo "<a href=\"#\">{$oCon['connome']}</a>";
                                $aSistema = Conexao::getConexao()->query("select * from webbased.tbsistema "
                                        . "where concodigo = {$oCon['concodigo']}")->fetchAll(PDO::FETCH_ASSOC);
                                echo "<ul class=\"sistema\">";
                                foreach ($aSistema as $idx => $oSistema) {
                                    echo "<li><a href=\"{$oSistema['siscodigo']}\" conjunto=\"{$oSistema['siscodigo']}\" "
                                            . "onclick=\"\""
                                            . ">{$oSistema['sisnome']}</a></li>
                                        ";
                                }
                                echo "</ul>";
                                echo "</li>";
                            }
                        ?>
                    </ul>
                </div>
            </nav>
        </aside>
        <header>
            <div class="menu">
                <ul>
                    <?php
                        $aPath = explode('/', $path);
                        $iIdxSistema = array_search('sistema', $aPath);
                        $iSistema = $aPath[$iIdxSistema+1];
                        $aMod = Conexao::getConexao()->query("select * from webbased.tbmodulo where siscodigo = $iSistema")->fetchAll(PDO::FETCH_ASSOC);
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
        <script src="/comportamento/main.js"></script>
        <script src="/comportamento/tela_padrao.js"></script>
    </body>
</html>