<h1> G-Code Reader (gcr) </h1>

<hr>

<h2>Functionality</h3>
<p>Provides and interface to read in g-code commands from g-code files. Mainly targeted at reading the subset g-code commands and syntax that 3d printer slicers produce.</p>

<hr>

<h2>Supported G-code Syntax</h3>
<p>The below syntax definitions are subset of the NIST RS274NGC interpreter version 3, mixed and modified with various other source. The G-Code Reader (grc) suppoerts the below syntax defintions.</p>

<br>

<p><b>Syntax Errors</b><br>
Any syntax not specified is illegal and will cause an error.</p>

<br>

<p><b>Line Format</b><br>
A line consists of the following parts, in order:
<ul>
  <li>0 to 1 commands (command format)</li>
  <li>0 to 1 comments (comment format)</li>
  <li>1 to 1 line feeds and or carriage returns</li>
</ul>
The following also applies to a line:
<ul>
  <li>1 to 256 characters in length.</li>
  <li>Blank lines are allowed, and are ignored.</li>
</ul></p>

<br>

<p><b>Command Format</b><br>
A command consists of the following parts, in order:
<ul>
  <li>0 to N spaces and or tabs</li>
  <li>1 to 1 lower or upper case letters</li>
  <li>0 to N spaces and or tabs</li>
  <li>1 to 5 digits</li>
  <li>0 to N parameters (parameter format)</li>
</ul>
The following also applies to a word:
<ul>
  <li>Letter character is case insensitive.</li>
</ul></p>

<br>

<p><b>Parameter Format</b><br>
A command consists of the following parts, in order:
<ul>
  <li>0 to N spaces and or tabs</li>
  <li>1 to 1 lower or upper case letters</li>
  <li>0 to 1 numbers (number format)</li>
</ul>
The following also applies to a word:
<ul>
  <li>Letter character is case insensitive.</li>
</ul></p>

<br>

<p><b>Number Format</b><br>
A number consists of the following parts, in order:
<ul>
  <li>0 to N spaces and or tabs</li>
  <li>0 to 1 plus or minus signs</li>
  <li>1 to N digits</li>
  <li>0 to 1 periods</li>
  <li>0 to N digits</li>
</ul>
The following also applies to a number:
<ul>
  <li>Numbers without a sign are treated as positive values.</li>
  <li>Numbers without a period are treated as signed integer values.</li>
  <li>Numbers with a period are treated as floating point values.</li>
</ul></p>

<br>

<!--
<p><b>NAME Format</b><br>
NAMEs consists of the following parts, in order:
<ol>
  <li></li>
  <li></li>
  <li></li>
</ol>
The following also applies to NAMEs:
<ul>
  <li></li>
  <li></li>
  <li></li>
</ul> 
</p>
--!>

