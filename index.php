<?php
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Methods: POST, GET, OPTIONS');
?>
<!DOCTYPE html>
<html>
    <head>
    	<meta charset="utf-8">
    	<title>Projet IOTIA</title>
    	<link rel="stylesheet" href="index2.css" />
    	<script type="text/javascript">


    	</script>
    </head>
    <body>
    	<!--Header de la page -->

    	<header>
    		<div id="Conteneur">

    			<div class="element" id="element1">  <!--Elément 1-->
				<label for="nom" id="nom">DOM-IOTIA </label>
				<input type="button" id="bdr" name="bdr" value="Notification">
    			</div>
    		</div>

    		
    	</header>

    	<!--Barre de navigation -->
           <!-- <div id="Conteneur2">

                <div class="element" id="Titre1">Cette page vous présente les différentes données récoltées par les capteurs de la maison. </div>

                <div class="element" id="element1">  !--Elément 1--
                    <br><br><br>
                    <div class="element" id="element3">What is Lorem Ipsum?
                        Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. </div>
                    <label for="nom" id="nom"> </label>
                    <input type="button" id="st" name="St" value="statut">
                </div>
                <br><br><br>
            </div> -->

            <table>
                <tr>
                    <th scope="col">Capteur</th>
                    <th scope="col">Valeur</th>
                    <th scope="col">Etat de la fenêtre</th>
                </tr>
                <tr>
                    <th scope="row">Capteur de pluie</th>
                    <td>4,569</td>
                    <td>
                        <input type="button" id="st" name="St" value="Ouverte">
                        <br>
                        <input type="button" id="st" name="St" value="Fermée">
                    </td>
                </tr>
                <tr>
                    <th scope="col">Capteur</th>
                    <th scope="col">Valeur</th>
                    <th scope="col">Action</th>
                </tr>
                <tr>
                    <th scope="row">Capteur de température</th>
                    <td>7,223</td>
                    <td>
                        <input type="button" id="st" name="St" value="Climatiseur">
                        <br>
                        <input type="button" id="st" name="St" value="Chauffage">
                    </td>
                </tr>
                <tr>
                    <th scope="col">Capteur</th>
                    <th scope="col">Valeur</th>
                    <th scope="col">Lumière</th>
                </tr>
                <tr>
                    <th scope="row">Photorésistance</th>
                    <td>4,569</td>
                    <td>
                        <input type="button" id="st" name="St" value="Allumée">
                        <br>
                        <input type="button" id="st" name="St" value="Eteinte">
                    </td>
                </tr>
                <tr>
                    <th scope="col">Capteur</th>
                    <th scope="col">Valeur</th>
                    <th scope="col">Action</th>
                </tr>
                <tr>
                    <th scope="row">Capteur d'humidité</th> 
                    <td>4,569</td>
                    <td>
                        <input type="button" id="st" name="St" value="Climatiseur">
                        <br>
                        <input type="button" id="st" name="St" value="Chauffage">
                    </td>
                </tr>
            </table>

    	<nav>
    		
    	</nav>

    	<!--Footer de la page -->

    	<footer>
    		
    	</footer>

    </body>
</html>



