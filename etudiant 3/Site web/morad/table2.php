
<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
    <meta charset="utf-8">
    <title></title>
    <link rel="stylesheet" href="table.css">
  </head>

  <body>
    <?php

    include('zero/config.php'); // Pour la connexion bdd

    if (PDO) {

    $sql = "SELECT * FROM utilisateurs";
    $res = $bdd->prepare($sql);
    $res->execute();

    echo "<table><tr>
            <th>ID</th>
            <th>Pseudo</th>
            <th>Email</th>
            <th>Date d'insription</th>
            <th>Type</th>
           </tr>";
    /*$row = $res->fetch(PDO::FETCH_ASSOC);
    echo $row["Type"];*/

    while($row = $res->fetch(PDO::FETCH_ASSOC)){
            echo "<tr>
                      <td>".$row["id"]."</td>
                      <td>".$row["pseudo"]."</td>
                      <td>".$row["email"]."</td>
                      <td>".$row["date_inscription"]."</td>
                      <td>".$row["Type"]."</td>
                  </tr>
            ";
            }
      echo "</table>";

    }
    ?>
  </body>
</html>
