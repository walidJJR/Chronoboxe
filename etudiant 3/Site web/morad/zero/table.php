<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
    <meta charset="utf-8">
    <link rel="stylesheet" href="table.css">
    <title>Admin dashboard</title>
  </head>
  <body>
    <?php
        session_start();
        require_once 'config.php'; // ajout connexion bdd
       // si la session existe pas soit si l'on est pas connecté on redirige
        if(!isset($_SESSION['user'])){
            header('Location:boxe.php');
            die();
        }

        // On récupere les données de l'utilisateur
        $req = $bdd->prepare('SELECT * FROM utilisateurs WHERE token = ?');
        $req->execute(array($_SESSION['user']));
        $data = $req->fetch();

    ?>



<table>

  <?php
  include 'config.php';
  $sql =  'SELECT name, color, utilisateurs FROM fruit ORDER BY name';
  foreach  ($conn->query($sql) as $row) {
      print $row['id'] . "\t";
      print  $row['pseudo'] . "\t";
      print  $row['date_Inscription'] . "\t"
      print  $row['Type'] . "\t"

      print $row['email'] . "\n";
  }
  ?>







</table>






  </body>
</html>
