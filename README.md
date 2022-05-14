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
  <li>Mandatory command word,</li>
  <li>Optional parameter word(s).</li>
  <li>Optional comment.</li>
  <li>Mandatory carriage return ('\n') and or line feed ('\r') character(s).</li>
</ol>
The following also applies to lines:
<ul>
  <li>Up to 256 characters long.</li>
  <li>Blank lines are allowed, and are ignored.</li>
  <li>Any number of space (' ') and or tab ('\t') characters can be before, after, and or between the above parts.</li>
</ul></p>

<br>

<p><b>Word Format</b><br>
A word consists of the following parts, in order:
<ol>
  <li>Mandatory letter character ('A'-'Z', 'a'-'z').</li>
  <li>Optional number.</li>
</ol>
The following also applies to words:
<ul>
  <li>Letter character is case insensitive.</li>
  <li>Any number of spaces (' ') and or tabs ('\t') can be before, after, and or between the above parts.</li>
</ul></p>

<br>

<p><b>Number Format</b><br>
A number consists of the following parts, in order:
<ol>
  <li>Optional plus ('+') or minus ('-') sign character.</li>
  <li>Mandatory one or more digit ('0'-'9') characters.</li>
  <li>Optional decimal point ('.') character.</li>
  <li>Optional one or more digit ('0'-'9') characters.</li>
</ol>
The following also applies to NAMEs:
<ul>
  <li></li>
  <li></li>
  <li></li>
</ul></p>








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

