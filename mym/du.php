<? header('Content-type: text/html'); ?>
<?       $configfile1 = shell_exec(" ls ./.htaccess ");
         if(!$configfile1){
         print "<script>window.alert('�޴��� ���� ������ �������� �ʾ�, ó���� �����˴ϴ�..');history.go(-1)</script>";
         }
?>


<? include "head.htm"; ?>
<? include "../.htuserinfo.php"; ?>
<? echo "<body bgcolor=#F5F5F5 LINK=#555555 ALINK=#888888 VLINK=#3f3f3f TEXT=#000000 TOPMARGIN=20 LEFTMARGIN=10 MARGINWIDTH=0 ARGINHEIGHT=0>"; ?>
<? echo "&nbsp;<b>* <u>���� ��뷮 ��ȸ</u> (üũ��...) </b><br><br>"; ?>
<? flush(); ?>
<?
        $total = $hddlimit;             //�Ҵ���� �����뷮, ���� MByte ex)byus�� ��� 500(MB)

        exec("du -sk $rootdir", $array);
        $usedKB = (int)$array[0];       //����� ���� �뷮 ���� KByte

        $used = (int)($usedKB / 1000);  //������ KByte => MByte
        $free = $total - $used;
	if($free < 0) {$free = 0;};
	$usedp = (int)($used / $total * 100);
	if($usedp > 100) {$usedp = 100;};
	$freep = (int)(100 - $usedp);

echo "<table border=0 width=400 cellpadding=3 cellspacing=1 bgcolor=#B0BDD5>";
echo "<tr><td></td></tr>";
echo "<tr><td width=150 height=25 bgcolor=#E2E6EC><font size='2' color='#3D5C9A'>&nbsp;&nbsp; <b>���뷮</b></font></td>";
echo "<td width=250 align=right bgcolor=#FDFDFD><font size='2' color='#ff6666'> <b>$total Mbyte</b> &nbsp;</font></td></tr>";

echo "<tr><td bgcolor=#E2E6EC><font size='2' color='#3D5C9A'>&nbsp;&nbsp; <b>�����뷮</b></font></td>";
echo "<td align=right height=25 bgcolor=#FDFDFD><font size='2' color='#FF6666' title='$usedKB KByte' > <b>$used Mbyte</b> &nbsp;</font></td></tr>";

echo "<tr><td bgcolor=#E2E6EC><font size='2' color='#3D5C9A'>&nbsp;&nbsp; <b>�����뷮</b></font></td>";
echo "<td align=right height=25 bgcolor=#FDFDFD><font size='2' color='#FF6666'> <b>$free Mbyte</b> &nbsp;</font></td></tr>";
echo "</table>";
echo "<table border=0 cellspacing=0 cellpadding=0 width=400>";
echo "<tr><td><br><br><br>";

// $percent�� ��Ÿ�� %������ �迭�� ����
// �Ʒ��� 2%,4%,6%,8%,10%,12%,14%,16%,18% �� ��Ÿ���ϴ�
$percent=array(0,$freep,$usedp);
// ������ ��� ���� �� �Դϴ�. �ѱ��� �۲��� �ʿ��ϴٴ� �� �ٵ� �ƽ�����
$string=array("$free MB free", "$used MB Used");

// $percent�� ���� 100%�� �Ѱų� ���ڶ��� üũ, ������ ����, ���ڶ�� �������� 100%(360��)�߰�
for($i=0;$i<sizeof($percent);$i++){
        $sum +=$percent[$i];
        $arc +=round(360*$percent[$i]/100);
        $x[]=$arc;
}
if($sum > 100) {echo "100%�� �Ѿ����ϴ�.";exit;}
if($sum < 100) {$x[]=360;$percent[]=100-$sum;}
else $x[sizeof($percent)-1]=360;

// �̹���ũ�� ���δ� 400���� ��ŭ(���ھ�������), ���δ� ������ �ݺ��� ��ŭ(3Dȿ���κ�)
$size_x=400;
$size_y=$size_x/2;
$size_z=$size_y/10;
$image = imagecreate(($size_x+50), ($size_y+$size_z));
//imagecreatetruecolor()�� ���� imagecolortransparent()�Լ��� �ȵ�
//$image = imagecreatetruecolor($size_x, ($size_y+$size_z));

// ���� ����, bc[]�� ������ ���� �κ�, dc[]�� 3D�� ��ο� �κл�
$white = imagecolorallocate($image, 0xFF, 0xFF, 0xFF);
$black = imagecolorallocate($image, 0x00, 0x00, 0x00);
$gray  = imagecolorallocate($image, 0xF6, 0xF6, 0xF6);
$bc[0] = imagecolorallocate($image, 0xC0, 0xC0, 0xC0);//gray
$dc[0] = imagecolorallocate($image, 0x90, 0x90, 0x90);//darkgray
$bc[1] = imagecolorallocate($image, 0x58, 0x8E, 0xCD);
$dc[1] = imagecolorallocate($image, 0x4A, 0x7A, 0xB3);
$bc[2] = imagecolorallocate($image, 0x47, 0xB8, 0xB5);
$dc[2] = imagecolorallocate($image, 0x39, 0xA0, 0x9D);
$bc[3] = imagecolorallocate($image, 0x9F, 0xB8, 0xE1);
$dc[3] = imagecolorallocate($image, 0x88, 0xA0, 0xC5);
$bc[4] = imagecolorallocate($image, 0x87, 0xCD, 0xCC);
$dc[4] = imagecolorallocate($image, 0x71, 0xB3, 0xB1);
$bc[5] = imagecolorallocate($image, 0xC4, 0xE1, 0xBE);
$dc[5] = imagecolorallocate($image, 0xA9, 0xC5, 0xA4);
$bc[6] = imagecolorallocate($image, 0x87, 0xCD, 0xCC);
$dc[6] = imagecolorallocate($image, 0x71, 0xB3, 0xB1);
$bc[7] = imagecolorallocate($image, 0xC4, 0xE1, 0xBE);
$dc[7] = imagecolorallocate($image, 0xA9, 0xC5, 0xA4);
$bc[8] = imagecolorallocate($image, 0x47, 0xB8, 0xB5);
$dc[8] = imagecolorallocate($image, 0x39, 0xA0, 0x9D);
$bc[9] = imagecolorallocate($image, 0x9F, 0xB8, 0xE1);
$dc[9] = imagecolorallocate($image, 0x88, 0xA0, 0xC5);
$bc[10] = imagecolorallocate($image, 0x58, 0x8E, 0xCD);
$dc[10] = imagecolorallocate($image, 0x4A, 0x7A, 0xB3);
$bc[11] = imagecolorallocate($image, 0xC0, 0xC0, 0xC0);//gray
$dc[11] = imagecolorallocate($image, 0x90, 0x90, 0x90);//darkgray

// make the 3D effect ���ٸ� ���Ͽ��µ� ���� �������� ���� ����
for ($i = ($size_y/2+$size_z); $i > ($size_y/2); $i--) {
        for($j=0;$j<sizeof($percent);$j++){
                imagefilledarc($image, ($size_x/2), $i, $size_x, $size_y, $x[$j], $x[$j+1] , $dc[$j], IMG_ARC_PIE);
        }
}

// ���� �����׸�
for ($j=0;$j<sizeof($percent);$j++){
        imagefilledarc($image, ($size_x/2), ($size_y/2), $size_x, $size_y, $x[$j], $x[$j+1] , $bc[$j], IMG_ARC_PIE);
}

// �Ʒ����ʹ� ������ �ִºκ��Դϴ�.
for($i=0;$i<sizeof($x)-1;$i++){
        $spot[]=intval(($x[$i]+$x[$i+1])/2);
}
$z=intval($size_x*2/5);
$zz=intval($size_y*2/5);
for($i=0;$i<sizeof($spot);$i++){
        $x=intval(cos(deg2rad($spot[$i]))*$z)+200;
        $y=intval(sin(deg2rad($spot[$i]))*$zz)+100;
        imagestring($image,3,$x,$y,$percent[$i+1]."% ".$string[$i],$black);
        imagefilledrectangle($image,$x-2,$y-2,$x+2,$y+2,$gray);
}

// ����ó��
imagecolortransparent($image,$white);

// �̹������
imagepng($image,"du.png");
imagedestroy($image);
exec ("chmod 707 $rootdir"."mym/du.png");

$time = time();
echo "<img src=du.png?rnd=$time>";
echo "</td></tr></table></body>";
?>
