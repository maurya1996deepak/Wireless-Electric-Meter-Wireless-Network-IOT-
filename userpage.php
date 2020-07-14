<?php
date_default_timezone_set('Asia/Kolkata');
$date = date('Y-m-d h:i');
echo $date;

 
if(isset($_GET['meterno']))
{
 $meterno=$_GET['meterno'];


 
 
   include 'connection.php';
        $query="SELECT * FROM energydata WHERE meternumber='$meterno'";
	    $run=mysqli_query($conn,$query);
		$data=mysqli_fetch_assoc($run);
		$totalunit=$data['totalunit'];
		$totalbill=$data['totalbill'];
		$totalpayed=$data['totalpayed'];
		$remainamount=$data['remainamount'];
		$meternumber=$data['meternumber'];
		$name=$data['name'];
		
	   
}
?>
<html>
<table border="2">
     <tr>
	 <th >Name</th><th>Meter Number</th><th>Total  Units Consumed</th><th>Total Bill</th><th>Total Bill Paid</th><th>Remaining</th>
	 </tr>
     <tr>
	   <td><?php echo $name;  ?></td><td><?php echo $meternumber;  ?></td><td><?php echo $totalunit;  ?></td><td><?php echo $totalbill; ?></td><td><?php echo $totalpayed; ?></td><td><?php echo $remainamount; ?></td>
     </tr>
     
   </table>
</html>


