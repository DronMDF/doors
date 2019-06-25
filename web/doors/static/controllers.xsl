<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
>

<xsl:template match="/controllers">
<html>
<head>
<title>Список контроллеров</title>
</head>
<body>
	<xsl:for-each select="controller">
	Контроллер
	<a>
		<xsl:attribute name="href">/controllers/<xsl:value-of select="@id"/></xsl:attribute>
		<xsl:value-of select="address"/>:<xsl:value-of select="port"/>
	</a>
	<br/>
	</xsl:for-each>
</body>
</html>
</xsl:template>
</xsl:stylesheet>
