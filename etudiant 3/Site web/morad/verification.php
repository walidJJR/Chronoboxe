<?php


if(isset($_POST['username']) && isset($_POST['password']))
{
   // connexion à la base de données
    $db_username = 'pi';
    $db_password = 'bonjour';
    $db_name     = 'chronoboxe';
    $db_host     = 'localhost';
    $db = mysqli_connect( $db_host, $db_username, $db_password ,$db_name )
    or die('could not connect to database');

    // on applique les deux fonctions mysqli_real_escape_string et htmlspecialchars
    // pour éliminer toute attaque de type injection SQL et XSS
    $username = mysqli_real_escape_string($db,htmlspecialchars($_POST['username']));
    $password = mysqli_real_escape_string($db,htmlspecialchars($_POST['password']));

    if($username !== "" && $password !== "")
    {
       $requete = "SELECT count(*) FROM Utilisateur where nom_utilisateur = '".$username."' and mot_de_passe = '".$password."' ";
        $exec_requete = mysqli_query($db,$requete);
        $reponse      = mysqli_fetch_array($exec_requete);
        $count = $reponse['count(*)'];



        if($count!=0) // nom d'utilisateur et mot de passe correctes
        {
          if($username == "admin" && $password == "admin"){
            $_SESSION['username'] = $pi;
            header('Location: ChronoBoxeSite.html');
          }else{
            $_SESSION['username'] = $pi;
            header('Location: principal.php');
          }


        }
        else
        {
           header('Location: login.php?erreur=1'); // utilisateur ou mot de passe incorrect
         }
      }
    else
    {
       header('Location: login.php?erreur=2'); // utilisateur ou mot de passe vide
    }
   }
   else
   {

       header('Location: login.php');

   }


   mysqli_close($db); // fermer la connexion
   var_dump($_POST);
   exit();
   ?>
