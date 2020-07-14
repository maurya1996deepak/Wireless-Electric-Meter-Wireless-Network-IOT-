<?php
date_default_timezone_set('Asia/Kolkata');
$date = date('Y-m-d h:i:S');


 
if(isset($_GET['field1']))
{
 $unit=$_GET['field1'];
 $meterno=$_GET['mn'];
 
 
  include 'connection.php';
 $query="UPDATE energydata
         SET totalunit = $unit 
		 WHERE meternumber = $meterno;";
         $run=mysqli_query($conn,$query);
         mysqli_close($conn);
 
 
        include 'connection.php';
        $query="SELECT * FROM energydata WHERE meternumber='$meterno'";
	    $run=mysqli_query($conn,$query);
		$data=mysqli_fetch_assoc($run);
		$totalunit=$data['totalunit'];
		$totalbill=$totalunit * 4;
		$totalpayed=$data['totalpayed'];
		$remainamount=$totalbill-$totalpayed;
	    mysqli_close($conn);
        include 'connection.php';
        $query="UPDATE energydata
                SET totalunit = $unit , totalbill=$totalbill , remainamount=$remainamount
		
                WHERE meternumber = $meterno;";
        $run=mysqli_query($conn,$query);
        mysqli_close($conn);
        include 'connection.php';
        $query="UPDATE energydata
         SET lastdateupdate = $date
		 WHERE meternumber = $meterno;";
		 $run=mysqli_query($conn,$query);
         mysqli_close($conn);
}



?>
