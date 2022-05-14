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
<ol>
  <li>One command word.</li>
  <li>Zero or more parameter words.</li>
  <li>Zero or more comments.</li>
  <li>One carriage return ('\n') and or line feed ('\r') character.</li>
</ol>
The following also applies to a line:
<ul>
  <li>Up to 256 characters in length.</li>
  <li>Blank lines are allowed, and are ignored.</li>
  <li>Zero or more space (' ') and or tab ('\t') characters can be before, after, and or between the above parts.</li>
</ul></p>

<br>

<p><b>Word Format</b><br>
A word consists of the following parts, in order:
<ol>
  <li>One letter character ('A'-'Z', 'a'-'z').</li>
  <li>Zero to one numbers.</li>
</ol>
The following also applies to a word:
<ul>
  <li>Letter character is case insensitive.</li>
  <li>Zero or more space (' ') and or tab ('\t') characters can be before, after, and or between the above parts.</li>
</ul></p>

<br>

<p><b>Number Format</b><br>
A number consists of the following parts, in order:
<ol>
  <li>Zero to one plus ('+') or minus ('-') sign characters.</li>
  <li>One or more digit ('0'-'9') characters.</li>
  <li>Zero to one period ('.') characters.</li>
  <li>Zero or more digit ('0'-'9') characters.</li>
</ol>
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

