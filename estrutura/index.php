<?php

require_once './autoload.php';

?>

<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8">
        <title>ERP</title>
        <title>title</title>
        <link rel="stylesheet" href="style/main.css"/>
    </head>
    <body>
        <header>
            <div class="menu">
                <ul>
                    <li>
                        <?php
                            foreach (['Cadastro', 'Gestão'] as $menu) {
                                echo "<a href=\"#\">$menu</a>";
                                echo "<div class=\"submenu\">";
                                foreach (['Aluno', 'Estabelecimento', 'Turma'] as $rotina) {
                                    echo "<ul>
                                        <li><a id=\"rotina\" href=\"#\" rotina=\"92001\" acao=\"101\" onclick=\"abre_nova_janela()\">$rotina</a></li>
                                    </ul>";
                                }
                                echo "</div>";
                            }
                        ?>
                    </li>
                </ul>
            </div>
        </header>
        <div class="janela" id="janela">
            <header>Consultar Turmas</header>
        </div>
        <script src="https://code.jquery.com/jquery-3.7.1.min.js"></script>
        <script src="comportamento/main.js"></script>
    </body>
</html>
