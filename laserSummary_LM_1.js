
$(function() {
	'use strict';
	var crateNum = parseInt($('crtnum').text());
	var timeout = 1000;
	var lmprefix = 'lm';
	var smprefix = 'sm';
	var maxChannel = 30;

	Array.prototype.avg = Array.prototype.avg || function () {
	    return this.reduce(function(p,c,i,a){return p+(c/a.length)},0);
	};

	Array.prototype.size = Array.prototype.size || function () {
	    return this.reduce(function(p,c,i,a){return a.length},0);
	};

	var channels = [];

	channels[0] = 25-25;//pmt_1
	channels[1] = 26-25;//pid1_1
	channels[2] = 27-25;//pid2_1
	channels[3] = 20;//lm10_1
	channels[4] = 20;//lm11_1
	channels[5] = 23;//lm20_1
	channels[6] = 23;//lm21_1
	channels[7] = 21;//lm30_1
	channels[8] = 21;//lm31_1
	channels[9] = 22;//lm40_1
	channels[10] = 22;//lm41_1

	channels[11] = 30-25;//pmt_2
	channels[12] = 31-25;//pid1_2
	channels[13] = 32-25;//pid2_2
	channels[14] = 11;//lm10_2
	channels[15] = 11;//lm11_2
	channels[16] = 17;//lm20_2
	channels[17] = 17;//lm21_2
	channels[18] = 12;//lm30_2
	channels[19] = 12;//lm31_2
	channels[20] = 14;//lm40_2
	channels[21] = 14;//lm41_2

	channels[22] = 35-25;//pmt_3
	channels[23] = 36-25;//pid1_3
	channels[24] = 37-25;//pid2_3
	channels[25] = 15;//lm10_3
	channels[26] = 15;//lm11_3
	channels[27] = 18;//lm20_3
	channels[28] = 18;//lm21_3
	channels[29] = 5;//lm30_3
	channels[30] = 5;//lm31_3
	channels[31] = 0;//lm40_3
	channels[32] = 0;//lm41_3

	channels[33] = 40-25;//pmt_4
	channels[34] = 41-25;//pid1_4
	channels[35] = 43-25;//pid2_4
	channels[36] = 6;//lm10_4
	channels[37] = 6;//lm11_4
	channels[38] = 7;//lm20_4
	channels[39] = 7;//lm21_4
	channels[40] = 9;//lm30_4
	channels[41] = 9;//lm31_4
	channels[42] = 1;//lm40_4
	channels[43] = 1;//lm41_4

	channels[44] = 49-25;//pmt_5
	channels[45] = 46-25;//pid1_5
	channels[46] = 48-25;//pid2_5
	channels[47] = 2;//lm10_5
	channels[48] = 2;//lm11_5
	channels[49] = 8;//lm20_5
	channels[50] = 8;//lm21_5
	channels[51] = 3;//lm30_5
	channels[52] = 3;//lm31_5
	channels[53] = 4;//lm40_5
	channels[54] = 4;//lm41_5

	channels[55] = 50-25;//pmt_6
	channels[56] = 51-25;//pid1_6
	channels[57] = 52-25;//pid2_6
	channels[58] = 16;//lm10_6
	channels[59] = 16;//lm11_6
	channels[60] = 13;//lm20_6
	channels[61] = 13;//lm21_6
	channels[62] = 19;//lm30_6
	channels[63] = 19;//lm31_6
	channels[64] = 10;//lm40_6
	channels[65] = 10;//lm41_6
    
	var laserNum = [];
	for(var i = 0; i < 6; i++) 
	  laserNum[i]=i+1;
	
	var pmt = [];//0;
	for(var i = 0; i < 6; i++)
	    pmt[i]=0;

	var pid1 = [];//1;
	for(var i = 0; i < 6; i++)
	    pid1[i] = 1;

	var pid2 = [];//2;
	for(var i = 0; i < 6; i++)
	    pid2[i] = 2;

	var lm10 = [];//3;
	for(var i = 0; i < 6; i++)
	    lm10[i] = 3;

	var lm11 = [];//3;
	for(var i = 0; i < 6; i++)
	    lm11[i] = 3;

	var lm20 = [];//4;
	for(var i = 0; i < 6; i++)
	    lm20[i] = 4;

	var lm21 = [];//4;
	for(var i = 0; i < 6; i++)
	    lm21[i] = 4;

	var lm30 = [];//5;
	for(var i = 0; i < 6; i++)
	    lm30[i] = 5;

	var lm31 = [];//5;
	for(var i = 0; i < 6; i++)
	    lm31[i] = 5;

	var lm40 = [];//6;
	for(var i = 0; i < 6; i++)
	    lm40[i] = 6;

	var lm41 = [];//6;
	for(var i = 0; i < 6; i++)
	    lm41[i] = 6;
	
	for(var j = 0; j < 6; j++){
	    for(var i = 0; i < 6; i++){
		if (laserNum[j] == i + 1){
		    pmt[j] = channels[10*i + laserNum[j] - 1];
		    pid1[j] = channels[10*i + laserNum[j]];
		    pid2[j] = channels[10*i + 1 + laserNum[j]];
		    lm10[j] = channels[10*i + 2 + laserNum[j]];
		    lm11[j] = channels[10*i + 3 + laserNum[j]];
		    lm20[j] = channels[10*i + 4 + laserNum[j]];
		    lm21[j] = channels[10*i + 5 + laserNum[j]];
		    lm30[j] = channels[10*i + 6 + laserNum[j]];
		    lm31[j] = channels[10*i + 7 + laserNum[j]];
		    lm40[j] = channels[10*i + 8 + laserNum[j]];
		    lm41[j] = channels[10*i + 9 + laserNum[j]];
		}
	    }
	}

	function setAlarms(data) {
            var lmamps = data.runningAvgHists[lmprefix + 'AMPS'+crateNum.toString() + "_0"];
            var smamps = data.runningAvgHists[smprefix + 'AMPS'+crateNum.toString() + "_0"];
            var lmamps2 = data.runningAvgHists[lmprefix + 'AMPS'+crateNum.toString() + "_0_2"];
            $eventNum.text(smamps.eventNum);
            $runNum.text(smamps.runNum);
	    if (typeof lmamps !== 'undefined' && typeof smamps !== 'undefined' && typeof lmamps2 !== 'undefined'){
                for(var i = 0; i < 6; i++){
                    var a = 'btn1';
                    if(i==1)a='btn2';if(i==2)a='btn3';if(i==3)a='btn4';if(i==4)a='btn5';if(i==5)a='btn6';
                    if( smamps.last[channels[11*i]] > 100 &&//pmt 
			smamps.last[channels[11*i + 1]] > 100 &&//pid1
			smamps.last[channels[11*i + 2]] > 100 &&//pid2
			lmamps.last[channels[11*i + 3]] > 100 &&//lm10 
			lmamps2.last[channels[11*i + 4]] > 1//lm11
			){
			document.getElementById(a).style.background='green';
		    }
		    else{
                        document.getElementById(a).style.background='red';
                    }
                }
            }
	}
	
	function setPage(j) {//j is laser number
	    lp1History[j]=document.getElementById('lp'+(j+1).toString()+'1History');
	    lp2History[j]=document.getElementById('lp'+(j+1).toString()+'2History');
	    lp3History[j]=document.getElementById('lp'+(j+1).toString()+'3History');
	    lp4History[j]=document.getElementById('lp'+(j+1).toString()+'4History');
	    
	    //Three or four plots overlaid - PD1, PD2 and PMT	
	    Plotly.newPlot('lp'+(j+1).toString()+'1History', [
                                                            { y: [],  type: 'scatter', mode: 'lines' },{ y: [],  type: 'scatter', mode: 'lines'}],
			   {			
			       xaxis: { title: 'Event num', 'titlefont': { size: 15 }}, //, range: [0, 15000] },                             
				   yaxis: { title: 'Amplitude', titlefont: { size: 15 }, autorange:'true'}
			       //legend: { orientation: 'h', font: { size: 10 } }                                                            
                           });
	    Plotly.newPlot('lp'+(j+1).toString()+'2History', [
							      { y: [],  type: 'scatter', mode: 'lines' },{ y: [],  type: 'scatter', mode: 'lines'}],
                           {
                               xaxis: { title: 'Event num', 'titlefont': { size: 15 }},
				   yaxis: { title: 'Amplitude', titlefont: { size: 15 }, autorange:'true'}
			   });
	    Plotly.newPlot('lp'+(j+1).toString()+'3History', [
							      { y: [],  type: 'scatter', mode: 'lines' },{ y: [],  type: 'scatter', mode: 'lines'}],
                           {
                               xaxis: { title: 'Event num', 'titlefont': { size: 15 }},
				   yaxis: { title: 'Amplitude', titlefont: { size: 15 }, autorange:'true'}
			   });
	    Plotly.newPlot('lp'+(j+1).toString()+'4History', [
							      { y: [],  type: 'scatter', mode: 'lines' },{ y: [],  type: 'scatter', mode: 'lines'}],
			   {
                               xaxis: { title: 'Event num', 'titlefont': { size: 15 }},
                                   yaxis: { title: 'Amplitude', titlefont: { size: 15 }, autorange:'true'}
                           });

	    socket.on('requested objects', function(data) {
		    setAlarms(data);				    
		    //LM pulses
		    lm11History[j] = data.histories[smprefix + 'AMP' + crateNum.toString()+ lm10[j] + "_0"];
                    lm12History[j] = data.histories[lmprefix + 'AMP' + crateNum.toString()+ lm11[j] + "_0_2"];
		    lm21History[j] = data.histories[lmprefix + 'AMP' + crateNum.toString()+ lm20[j] + "_0"];
                    lm22History[j] = data.histories[lmprefix + 'AMP' + crateNum.toString()+ lm21[j] + "_0_2"];
		    lm31History[j] = data.histories[lmprefix + 'AMP' + crateNum.toString()+ lm30[j] + "_0"];
                    lm32History[j] = data.histories[lmprefix + 'AMP' + crateNum.toString()+ lm31[j] + "_0_2"];
		    lm41History[j] = data.histories[lmprefix + 'AMP' + crateNum.toString()+ lm40[j] + "_0"];
                    lm42History[j] = data.histories[lmprefix + 'AMP' + crateNum.toString()+ lm41[j] + "_0_2"];
		   
		    //console.log("LM11",lm11History[1].y[10]);

		    setTimeout(function() {
			    if ( typeof pid1History[j] !== 'undefined') {
				
				Plotly.deleteTraces(lp1History[j], [0,1]);
				Plotly.addTraces(lp1History[j],[{x: pmtHistory[j].x, y: lm11History[j].y, name:'LM1-A1',mode: 'lines' , marker: { color: 'dimgray'}},
								{x: pmtHistory[j].x, y: lm12History[j].y, name:'LM1-A2',mode: 'lines' , marker: { color: 'black'}}]);
				
				    
				Plotly.deleteTraces(lp2History[j], [0,1]);
				Plotly.addTraces(lp2History[j],[{x: pid1History[j].x, y: lm21History[j].y, name:'LM2-A1',mode: 'lines' , marker: { color: 'purple'}},
								{x: pmtHistory[j].x, y: lm22History[j].y, name:'LM2-A2',mode: 'lines' , marker: { color: 'aqua'}}]);
				
				Plotly.deleteTraces(lp3History[j], [0,1]);
				Plotly.addTraces(lp3History[j],[{x: pmtHistory[j].x, y: lm31History[j].y, name:'LM3-A1',mode: 'lines' , marker: { color: 'chartreuse'}},
								{x: pmtHistory[j].x, y: lm32History[j].y, name:'LM3-A2',mode: 'lines' , marker: { color: 'brown'}}]);
				
				Plotly.deleteTraces(lp4History[j], [0,1]);
				Plotly.addTraces(lp4History[j],[{x: pmtHistory[j].x, y: lm41History[j].y, name:'LM4-A1',mode: 'lines' , marker: { color: 'darkgreen'}},
								{x: pid2History[j].x, y: lm42History[j].y, name:'LM4-A2',mode: 'lines' , marker: { color: 'gold'}}]);
				
			    }
			}, 0);
		});
	}
	
	var socket = io('/', { path: '/lasersocket' + crateNum });
	registerCommonCallbacks(socket);

	var pmtHistory = [];
	var pid1History = [];
	var pid2History = [];
	var lm11History = [];//Data for lm laser1 amp1 
        var lm12History = [];//Data for lm laser1 amp2
	var lm21History = [];//Data for lm laser2 amp1
	var lm22History = [];//Data for lm laser2 amp2
        var lm31History = [];//Data for lm laser3 amp1
        var lm32History = [];//Data for lm laser3 amp2
	var lm41History = [];//Data for lm laser4 amp1
        var lm42History = [];//Data for lm laser4 amp2

	var lp1History = [];//Plotly names for 4 lms
	var lp2History = [];//PLotly names for LM
	var lp3History = [];//Plotly names for 4 lms                                                                                             
	var lp4History = [];//PLotly names for LM  
	var ratio = [];
	//var ratio_norm = [];
	var ct=0;
	var pmt_avg=0;
	var pid1_avg=0;
	var pid2_avg=0;

	var $eventNum = $('#eventNum');                                                                                                    
	var $runNum = $('#runNum');

	for(var j=0; j<6; j++)
	    setPage(j);	

	// sochet calls for amps
	var historyStrings = [];
	historyStrings.push(lmprefix + 'nIslands' + crateNum.toString());
	historyStrings.push(smprefix + 'nIslands' + crateNum.toString());
	for (var i = 0; i < maxChannel; ++i) {
	    historyStrings.push(smprefix + 'AMP' + crateNum.toString() + i + "_0");
	    historyStrings.push(lmprefix + 'AMP' + crateNum.toString() + i + "_0");
	    historyStrings.push(lmprefix + 'AMP' + crateNum.toString() + i + "_0_2");
	}

	(function requestPlots() {
	    socket.emit('deliver objects', {
		    runningAvgHists: [lmprefix + 'AMPS'+crateNum.toString() + "_0",
				      lmprefix + 'AMPS'+crateNum.toString() + "_0_2",
				      smprefix + 'AMPS'+crateNum.toString() + "_0",
				      smprefix + 'AMPS'+crateNum.toString() + "_0_2"],
			histories: historyStrings
			});
	    setTimeout(requestPlots, timeout);
	})();

	socket.emit(lmprefix + 'nXtals?', crateNum);
	socket.emit(smprefix + 'nXtals?', crateNum);
	handleLaserModeUpdates();
    });
