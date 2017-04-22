<html>
<head>
	<title>Display old record</title>
	<script src="http://canvasjs.com/assets/script/canvasjs.min.js"></script>
	
	<script>
	<?php
			//Get all data from the file and return as a long string of JSON representation.
			function getData() {
				$file = file('sound_log.txt');
				echo json_encode($file);
			}
	?>
		/*handle the data given from PHP by splitting into a 3 dimension array
		 *1st layer contains the data of each line in the file.
		 *each element in 1st layer contains 2 elements which are the dates and
		 *the data. The data is also an array of 8 values.
		 */
		dataArr = <?php getData(); ?>;
		for (var i = 0;i<dataArr.length;i++) {
			dataArr[i] = dataArr[i].split(", ");
			dataArr[i][1] = dataArr[i][1].replace(/\r?\n|\r/g, "");
			dataArr[i][1] = dataArr[i][1].split(";");
			for (var j = 0; j<8;j++) 
				dataArr[i][1][j] = Number(dataArr[i][1][j]);
		}
		
		function calculateMax(n) {
			var max = 0;
			for (var i=0;i<8;i++) {
				if (max<dataArr[n][1][i]) 
					max = dataArr[n][1][i];
			}
			return max;
		}
		function calculateMin(n) {
			var min = 3000;
			for (i=0;i<8;i++) {
				if (min>dataArr[n][1][i]) 
					min = dataArr[n][1][i];
			}
			return min;
		}

		window.onload = function() {
			var dataPoints = [];
			var chart = new CanvasJS.Chart("chartcontainer");
			//Customize the chart by enabling the animations, change the themes, etc.
			chart.options.animationEnabled = "true";
			chart.options.animationDuration = 1000;
			chart.options.theme = "theme2";
			chart.options.title = {text: "Recorded sound", fontSize: 30, fontColor: "green"};
			chart.options.axisY = {title: "RMS values", interlacedColor: "#F0F8FF"};
			//Customize the toolTip to show data when hover the mouse to the designated dataPoint in the chart.
			chart.options.toolTip = {content: "{label} <br/> RMS values: <br/> minimum: {y[0]} , maximum: {y[1]}"};
			chart.options.axisX = {title: "Last modified: " + dataArr[dataArr.length-1][0], labelWrap:true};	//This will showcase the last time the chart is updated.
			
			//Push all the dataPoints into the chart.
			for (var i = 0;i<dataArr.length;i++) {
				dataPoints.push({y: [calculateMin(i), calculateMax(i) ], label: dataArr[i][0]});
			}
			//Define dataSeries which is the type of chart, and push the dataPoints in. 
			var series = { type: "rangeSplineArea"};
			chart.options.data = [];
			chart.options.data.push(series);
			series.dataPoints = dataPoints;
			
			//We have to call this built-in function to render the chart.
			chart.render();
		}

	</script>
</head>
<body>
	<div id = "chartcontainer" style ="height:360px; width:100%;"></div>
	<input type = "button" onclick ="location.href = 'recordLive.html';" value ="Record live data here" ></input>
</body>
</html>