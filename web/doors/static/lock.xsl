<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
>

<xsl:template match="/lock">
<html>
<head>
<title>Замок <xsl:value-of select="hwid"/></title>
</head>
<body>
	Состояние замка:
	<xsl:choose>
		<xsl:when test="open">открыт</xsl:when>
		<xsl:otherwise>закрыт</xsl:otherwise>
	</xsl:choose>
</body>
</html>
</xsl:template>
</xsl:stylesheet>
