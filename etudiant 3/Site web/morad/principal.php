<html>
    <head>
        <meta charset="utf-8">
        <!-- importer le fichier de style -->
        <link rel="stylesheet" href="principal.css" media="screen" type="text/css" />
    </head>
    <body>
        <div id="content">
            <!-- tester si l'utilisateur est connecté -->
            <?php
            
                if($_SESSION['username'] !== "pi"){
                    $user = $_SESSION['username'];
                    // afficher un message
                    echo "Bonjour $user, vous êtes connecté";
                }
            ?>
        </div>
    </body>
</html>
