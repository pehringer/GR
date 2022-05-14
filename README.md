<h1> G-Code Reader (gcr) </h1>

<hr>

<h2>Functionality</h3>
<p>Provides and interface to read in g-code commands from g-code files. Mainly targeted at reading the subset g-code commands and syntax that 3d printer slicers produce.</p>

<hr>

<h2>Supported G-code Syntax</h3>
<p>The below syntax definitions are subset of the NIST RS274NGC interpreter version 3, with a few minor changes. The G-Code Reader (grc) suppoerts the below syntax defintions.</p>

<p><b>Syntax Errors</b><br>
Any syntax not specified is illegal and will cause an error.</p>

<p><b>Line Format</b><br>
Lines consists of the following parts, in order:
<ol>
  <li>Optional line delete character ('/').</li>
  <li>Optional <b>line number</b>.</li>
  <li>Any number of <b>word</b>s, parameter settings, and comments.</li>
  <li>End of line character ('\n' and or '\r').</li>
</ol>
The following also applies to lines:
<ul>
  <li>Can be up to 256 characters long.</li>
  <li>Are case insensitive.</li>
  <li>Any number of spaces (' ') and or tabs ('\t') can be between or in any of the above parts.</li>
  <li>Blank lines are allowed, and are ignored.</li>
</ul> 
</p>


