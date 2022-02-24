clear variables;
% close all;
clc;
% FICHIER DE L'ETAPE 1
Lune_EULER = 'Etape01\EUL-S-P.txt';
Lune_DF    = 'Etape01\DIF-S-P.txt';
Lune_RK2   = 'Etape01\RK2-S-P.txt ';
Lune_RK4   = 'Etape01\RK4-S-P.txt'; 

% FICHIERS DE L'ETAPE 2
% Runge kutta 4
fName11    = 'Etape02\Lune_XY_2Forces.txt';
fName12    = 'Etape02\Terre_XY_2Forces.txt';
%Différences finies
fName21    = 'Etape02\Lune-S-P.txt';
fName22    = 'Etape02\Terre-S-P.txt';

%%FICHIERS DE L'ETAPE 3
%Runge-Kutta
SIMPLE_MERCURE_RK4 = "Etape03\simple_mercure_XY_RK4.txt";
SIMPLE_VENUS_RK4   = "Etape03\simple_venus_XY_RK4.txt";
SIMPLE_TERRE_RK4   = "Etape03\simple_terre_XY_RK4.txt";
SIMPLE_MARS_RK4    = "Etape03\simple_mars_XY_RK4.txt";
SIMPLE_JUPITER_RK4 = "Etape03\simple_jupiter_XY_RK4.txt";
SIMPLE_SATURNE_RK4 = "Etape03\simple_saturne_XY_RK4.txt";
SIMPLE_URANUS_RK4  = "Etape03\simple_uranus_XY_RK4.txt";
SIMPLE_NEPTUNE_RK4 = "Etape03\simple_neptune_XY_RK4.txt";
%Différences finies
SIMPLE_MERCURE_DF = "Etape03\MERCURE-S-P.txt";
SIMPLE_VENUS_DF   = "Etape03\VENUS-S-P.txt";
SIMPLE_TERRE_DF   = "Etape03\TERRE-S-P.txt";
SIMPLE_MARS_DF    = "Etape03\MARS-S-P.txt";
SIMPLE_JUPITER_DF = "Etape03\JUPITER-S-P.txt";
SIMPLE_SATURNE_DF = "Etape03\SATURNE-S-P.txt";
SIMPLE_URANUS_DF  = "Etape03\URANUS-S-P.txt";
SIMPLE_NEPTUNE_DF = "Etape03\NEPTUNE-S-P.txt";

%%FICHIERS DE L'ETAPE 4

%%% Runge-Kutta4
SOLEIL_RK4  = "RK4\Etape04\soleil_XY.txt";
MERCURE_RK4 = "RK4\Etape04\mercure_XY.txt";
VENUS_RK4   = "RK4\Etape04\venus_XY.txt";
TERRE_RK4   = "RK4\Etape04\terre_XY.txt";
MARS_RK4    = "RK4\Etape04\mars_XY.txt";
JUPITER_RK4 = "RK4\Etape04\jupiter_XY.txt";
SATURNE_RK4 = "RK4\Etape04\saturne_XY.txt";
URANUS_RK4  = "RK4\Etape04\uranus_XY.txt";
NEPTUNE_RK4 = "RK4\Etape04\neptune_XY.txt";
LUNE_RK4    = "RK4\Etape04\lune_XY.txt";

%%Les différences finies
MERCURE_DF = "Etape04\MERCURE-S-P9.txt";
VENUS_DF   = "Etape04\VENUS-S-P9.txt";
TERRE_DF   = "Etape04\TERRE-S-P9.txt";
MARS_DF    = "Etape04\MARS-S-P9.txt";
JUPITER_DF = "Etape04\JUPITER-S-P9.txt";
SATURNE_DF = "Etape04\SATURNE-S-P9.txt";
URANUS_DF  = "Etape04\URANUS-S-P9.txt";
NEPTUNE_DF = "Etape04\NEPTUNE-S-P9.txt";
LUNE_DF    = "Etape04\LUNE-S-P9.txt";
%%
disp(" 01 : Système Terre-Lune simplifé. ");
disp(" 02 : Système Terre-Lune. ");
disp(" 03 : Système Solaire Simplifié. ");
disp(" 04 : Système Solaire.")
select = input("Veuillez choisir une simulation :  ");
%%
if(select == 01)

      
%Read data from C file
%------------------------- Methode D'euler-------------------------------%
%-- Format string for each line of text
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
%-- Open the text file
fileID = fopen( Lune_EULER, 'r' );
%-- Read columns of data according to format string.
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
%-- Close the text file
fclose( fileID );
%-- Allocate imported array to column variable names
xL_EULER = dataArray{:, 1};       	yL_EULER = dataArray{:, 2};
%-- Clear temporary variables
clearvars filename delimiter formatSpec fileID dataArray ans;
%------------------------- Methode Des différences finies --------------%
%Read data from C file
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( Lune_DF, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xL_DF = dataArray{:, 1};       	yL_DF = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans;
%------------------------- Methode De RK2-------------------------------%
%Read data from C file
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( Lune_RK2, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xL_RK2 = dataArray{:, 1};       	yL_RK2 = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans;

%------------------------- Methode De RK4-------------------------------%
%Read data from C file
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( Lune_RK4, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xL_RK4 = dataArray{:, 1};       	yL_RK4= dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans;


%% Plot
figure(1);
plot( xL_EULER(2:end), yL_EULER(2:end),'ob','DisplayName','Euler'); grid on; hold on;
plot( xL_DF(2:end), yL_DF(2:end),'or','DisplayName','Différences finies');
plot( xL_RK2(2:end), yL_RK2(2:end),'ok','DisplayName','Runge-Kutta 2');
plot( xL_RK4(2:end), yL_RK4(2:end),'og', 'DisplayName','Runge-Kutta 4');
title('Etape 01 : Système Terre-Lune simplifié');

end
%%
if (select == 02)
    

disp(" 01 : Différences Finies. ");
disp(" 02 : Runge-Kutta4 ");
selectMethode = input("Veuillez choisir une méthode de calcul :  ");


if(selectMethode == 02)
%Read data from C file
%---------------Runge-Kutta4------------------------------------------%
%-- Trajectoire de la lune
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( fName11, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xL_RK4 = dataArray{:, 1};       	yL_RK4 = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans;

%-- Trajectoire de la terre
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( fName12, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xT_RK4 = dataArray{:, 1};       	yT_RK4 = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans;

%% plot
% RK4
figure(2);
plot( xL_RK4(2:end), yL_RK4(2:end),'k');hold on;grid on; plot( xT_RK4(2:end), yT_RK4(2:end),'b');
title (' Etape 02 : Runge-Kutta');

end

if(selectMethode == 01)
%---------------Differences finies-------------------------------------%
%-- Trajectoire de la lune
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( fName21, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xL_DF = dataArray{:, 1};       	yL_DF = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans;

%-- Trajectoire de la terre
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( fName22, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xT_DF = dataArray{:, 1};       	yT_DF = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans;

%% Plot
% Différences Finies
figure(1);
plot( xL_DF(2:end), yL_DF(2:end),'k');hold on;grid on; plot( xT_DF(2:end), yT_DF(2:end),'b');
title(' Etape 02 : Différences Finies');

end
end
%%
if (select ==03)
%Read data from C file
disp(" 01 : Différences Finies. ");
disp(" 02 : Runge-Kutta4 ");
selectMethode = input("Veuillez choisir une méthode de calcul :  ");


if(selectMethode == 02)
    
%-----------------------------Runge-Kutta4-------------------------%
%-- Mercure
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( SIMPLE_MERCURE_RK4, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xMercure_RK4 = dataArray{:, 1};       	yMercure_RK4 = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 

%-- Venus
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( SIMPLE_VENUS_RK4, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xVenus_RK4 = dataArray{:, 1};       	yVenus_RK4 = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 

%-- Terre
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( SIMPLE_TERRE_RK4, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xTerre_RK4 = dataArray{:, 1};       	yTerre_RK4 = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 

%-- Mars
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( SIMPLE_MARS_RK4, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xMars_RK4 = dataArray{:, 1};       	yMars_RK4 = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 


%-- Jupiter
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( SIMPLE_JUPITER_RK4, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xJupiter_RK4 = dataArray{:, 1};       	yJupiter_RK4 = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 


%-- Saturne
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( SIMPLE_SATURNE_RK4, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xSaturne_RK4 = dataArray{:, 1};       	ySaturne_RK4 = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 

%-- Uranus
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( SIMPLE_URANUS_RK4, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xUranus_RK4 = dataArray{:, 1};       	yUranus_RK4 = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 

%-- Neptune
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( SIMPLE_NEPTUNE_RK4, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xNeptune_RK4 = dataArray{:, 1};       	yNeptune_RK4 = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 

%% Plot

figure(2);
% Runge-Kutta4
hold on;grid on; 
plot( xMercure_RK4(2:end), yMercure_RK4(2:end),'r','DisplayName','Mercure');
plot( xVenus_RK4(2:end)  , yVenus_RK4(2:end),'k','DisplayName','Venus');
plot( xTerre_RK4(2:end)  , yTerre_RK4(2:end),'b','DisplayName','Terre');
plot( xMars_RK4(2:end)   , yMars_RK4(2:end),'g','DisplayName','Mars');
plot( xJupiter_RK4(2:end), yJupiter_RK4(2:end),'y','DisplayName','Jupiter');
plot( xSaturne_RK4(2:end), ySaturne_RK4(2:end),'k','DisplayName','Saturne');
plot( xUranus_RK4(2:end) , yUranus_RK4(2:end),'k','DisplayName','Uranus');
plot( xNeptune_RK4(2:end), yNeptune_RK4(2:end),'k','DisplayName','Neptune');
title(' Etape 03 : Runge-Kutta');

end

if (selectMethode == 01)
%-----------------------------Différences finies-------------------------%
%-- Mercure
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( SIMPLE_MERCURE_DF, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xMercure_DF = dataArray{:, 1};       	yMercure_DF = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 

%-- Venus
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( SIMPLE_VENUS_DF, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xVenus_DF = dataArray{:, 1};       	yVenus_DF = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 

%-- Terre
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( SIMPLE_TERRE_DF, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xTerre_DF = dataArray{:, 1};       	yTerre_DF = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 

%-- Mars
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( SIMPLE_MARS_DF, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xMars_DF = dataArray{:, 1};       	yMars_DF = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 


%-- Jupiter
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( SIMPLE_JUPITER_DF, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xJupiter_DF = dataArray{:, 1};       	yJupiter_DF = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 


%-- Saturne
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( SIMPLE_SATURNE_DF, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xSaturne_DF = dataArray{:, 1};       	ySaturne_DF = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 

%-- Uranus
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( SIMPLE_URANUS_DF, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xUranus_DF = dataArray{:, 1};       	yUranus_DF = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 

%-- Neptune
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( SIMPLE_NEPTUNE_DF, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xNeptune_DF = dataArray{:, 1};       	yNeptune_DF = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 
%%% Plot 
% Différences Finies
figure(1);
hold on;grid on; 
plot( xMercure_DF(2:end), yMercure_DF(2:end),'r','DisplayName','Mercure');
plot( xVenus_DF(2:end)  , yVenus_DF(2:end),'k','DisplayName','Venus');
plot( xTerre_DF(2:end)  , yTerre_DF(2:end),'b','DisplayName','Terre');
plot( xMars_DF(2:end)   , yMars_DF(2:end),'g','DisplayName','Mars');
plot( xJupiter_DF(2:end), yJupiter_DF(2:end),'y','DisplayName','Jupiter');
plot( xSaturne_DF(2:end), ySaturne_DF(2:end),'k','DisplayName','Saturne');
plot( xUranus_DF(2:end) , yUranus_DF(2:end),'k','DisplayName','Uranus');
plot( xNeptune_DF(2:end), yNeptune_DF(2:end),'k','DisplayName','Neptune');
title(' Etape 03 : Différences Finies');

end

end

%% 
if (select ==04)
 
disp(" 01 : Différences Finies. ");
disp(" 02 : Runge-Kutta4 ");
selectMethode = input("Veuillez choisir une méthode de calcul :  ");

if(selectMethode == 02)     
%-----------------------------Runge-Kutta4-------------------------%
%-- Mercure
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( MERCURE_RK4, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xMercure_RK4 = dataArray{:, 1};       	yMercure_RK4 = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 

%-- Venus
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( VENUS_RK4, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xVenus_RK4 = dataArray{:, 1};       	yVenus_RK4 = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 

%-- Terre
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( TERRE_RK4, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xTerre_RK4 = dataArray{:, 1};       	yTerre_RK4 = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 

%-- Mars
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( MARS_RK4, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xMars_RK4 = dataArray{:, 1};       	yMars_RK4 = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 


%-- Jupiter
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( JUPITER_RK4, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xJupiter_RK4 = dataArray{:, 1};       	yJupiter_RK4 = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 


%-- Saturne
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( SATURNE_RK4, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xSaturne_RK4 = dataArray{:, 1};       	ySaturne_RK4 = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 

%-- Uranus
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( URANUS_RK4, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xUranus_RK4 = dataArray{:, 1};       	yUranus_RK4 = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 

%-- Neptune
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( NEPTUNE_RK4, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xNeptune_RK4 = dataArray{:, 1};       	yNeptune_RK4 = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans;

%-- Lune
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( LUNE_RK4, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xLune_DF = dataArray{:, 1};       	yLune_DF = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 

figure(1);hold on;grid on; 
plot( xMercure_RK4(2:end), yMercure_RK4(2:end),'r','DisplayName','Mercure');
plot( xVenus_RK4(2:end)  , yVenus_RK4(2:end),'k','DisplayName','Venus');
plot( xTerre_RK4(2:end)  , yTerre_RK4(2:end),'b','DisplayName','Terre');
plot( xMars_RK4(2:end)   , yMars_RK4(2:end),'g','DisplayName','Mars');
plot( xJupiter_RK4(2:end), yJupiter_RK4(2:end),'y','DisplayName','Jupiter');
plot( xSaturne_RK4(2:end), ySaturne_RK4(2:end),'k','DisplayName','Saturne');
plot( xUranus_RK4(2:end) , yUranus_RK4(2:end),'k','DisplayName','Uranus');
plot( xNeptune_RK4(2:end), yNeptune_RK4(2:end),'k','DisplayName','Neptune');
plot( xLune_RK4(3:end), yLune_RK4(3:end),'r','DisplayName','Lune');
title(' Etape 04 : Runge-Kutta4');

end

%-----------------------------Différences finies-------------------------%

if(selectMethode == 01)
%-- Mercure
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( MERCURE_DF, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xMercure_DF = dataArray{:, 1};       	yMercure_DF = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 

%-- Venus
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( VENUS_DF, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xVenus_DF = dataArray{:, 1};       	yVenus_DF = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 

%-- Terre
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( TERRE_DF, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xTerre_DF = dataArray{:, 1};       	yTerre_DF = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 

%-- Mars
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( MARS_DF, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xMars_DF = dataArray{:, 1};       	yMars_DF = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 


%-- Jupiter
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( JUPITER_DF, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xJupiter_DF = dataArray{:, 1};       	yJupiter_DF = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 


%-- Saturne
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( SATURNE_DF, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xSaturne_DF = dataArray{:, 1};       	ySaturne_DF = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 

%-- Uranus
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( URANUS_DF, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xUranus_DF = dataArray{:, 1};       	yUranus_DF = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 

%-- Neptune
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( NEPTUNE_DF, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xNeptune_DF = dataArray{:, 1};       	yNeptune_DF = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 

%-- Lune
formatSpec = '%f%f%[^\n\r]';            delimiter = ' ';
fileID = fopen( LUNE_DF, 'r' );
dataArray = textscan( fileID, formatSpec, 'Delimiter', delimiter, 'MultipleDelimsAsOne', true, 'EmptyValue', NaN, 'ReturnOnError', false );
fclose( fileID );
xLune_DF = dataArray{:, 1};       	yLune_DF = dataArray{:, 2};
clearvars filename delimiter formatSpec fileID dataArray ans; 


figure(1);hold on;grid on; 
plot( xMercure_DF(2:end), yMercure_DF(2:end),'r','DisplayName','Mercure');
plot( xVenus_DF(2:end)  , yVenus_DF(2:end),'k','DisplayName','Venus');
plot( xTerre_DF(2:end)  , yTerre_DF(2:end),'b','DisplayName','Terre');
plot( xMars_DF(2:end)   , yMars_DF(2:end),'g','DisplayName','Mars');
plot( xJupiter_DF(2:end), yJupiter_DF(2:end),'y','DisplayName','Jupiter');
plot( xSaturne_DF(2:end), ySaturne_DF(2:end),'k','DisplayName','Saturne');
plot( xUranus_DF(2:end) , yUranus_DF(2:end),'k','DisplayName','Uranus');
plot( xNeptune_DF(2:end), yNeptune_DF(2:end),'k','DisplayName','Neptune');
plot( xLune_DF(3:end), yLune_DF(3:end),'r','DisplayName','Lune');
title(' Etape 04 : Différences Finies' );
end
       
end  