unit vsprogprogrammer;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, LResources, Forms, Controls, Graphics, Dialogs,
  StdCtrls, ExtCtrls;

type

  { TVSProg_Programmer }

  TVSProg_Programmer = class(TForm)
    btnOK: TButton;
    lbProgrammer: TListBox;
    pnlButton: TPanel;
    procedure btnOKClick(Sender: TObject);
  private
    { private declarations }
    FSerialNumber: string;
    function GetProgrammerCount: integer;
    function GetProgrammers(Index: integer): string;
  public
    function ProgrammerParser(var line: string): boolean;
    property ProgrammerCount: integer Read GetProgrammerCount;
    property Proggrammers[Index: integer]: string Read GetProgrammers;
    property SerialNumber: string Read FSerialNumber;
    { public declarations }
  end; 

var
  VSProg_Programmer: TVSProg_Programmer;

implementation

procedure TVSProg_Programmer.btnOKClick(Sender: TObject);
var
  i, len: integer;
begin
  if lbProgrammer.SelCount = 0 then
  begin
    Beep;
    MessageDlg('Error', 'You MUST select one.', mtError, [mbOK], 0);
    exit;
  end;
  if lbProgrammer.SelCount > 1 then
  begin
    Beep;
    MessageDlg('Error', 'You CAN ONLY select one.', mtError, [mbOK], 0);
    exit;
  end;

  for i := 0 to lbProgrammer.Count - 1 do
  begin
    if lbProgrammer.Selected[i] then
    begin
      len := Length(lbProgrammer.Items.Strings[i]);
      FSerialNumber := Copy(lbProgrammer.Items.Strings[i], len - 23, 24);
      break;
    end;
  end;

  Close;
end;

function TVSProg_Programmer.GetProgrammerCount: integer;
begin
  Result := lbProgrammer.Items.Count;
end;

function TVSProg_Programmer.GetProgrammers(Index: integer): string;
begin
  Result := lbProgrammer.Items.Strings[Index];
end;

function TVSProg_Programmer.ProgrammerParser(var line: string): boolean;
var
  strTmp: string;
  len: integer;
begin
  Result := True;
  if (Pos('versaloon', line) = 1) and (Pos(' on ', line) > 0) then
  begin
    // found
    strTmp := Copy(line, 1, Pos(' on ', line) - 1);
    len := Length(strTmp);
    FSerialNumber := Copy(strTmp, len - 23, 24);
    lbProgrammer.Items.Add(strTmp);
  end;
end;

initialization
  {$I vsprogprogrammer.lrs}

end.

