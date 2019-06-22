<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="xml"/>

<xsl:template match="/doxygen">
  <table>
    <tr><th>Метод</th><th>Описание</th></tr>
    <xsl:apply-templates select="//memberdef[@kind = 'function']"/>
  </table>
</xsl:template>

<xsl:template match="memberdef">
  <tr>
    <td><xsl:apply-templates select=".//name"/> <xsl:apply-templates select=".//argsstring"/></td>
    <td><xsl:apply-templates select=".//detaileddescription"/></td>
  </tr>
</xsl:template>
</xsl:stylesheet>

<!-- xsltproc -o out.html gf7n.xsl xml/class_a_a_l_1_1_polynom_g_f7_n.xml -->