<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" encoding="utf-8"/>

  <xsl:template match="/">
    <xsl:apply-templates select="//entryFree"/>
  </xsl:template>

  <xsl:template match="entryFree">
    <xsl:variable name="lemmaID"><xsl:value-of select="./@key"/></xsl:variable>	
    <xsl:variable name="lemmaLabel"><xsl:value-of select="./orth"/></xsl:variable>
    
    <xsl:value-of select="$lemmaID"/><xsl:text>		</xsl:text><xsl:value-of select="$lemmaID"/>
  </xsl:template>

</xsl:stylesheet>