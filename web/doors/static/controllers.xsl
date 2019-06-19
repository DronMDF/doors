<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:template match="/controllers">
<html>
<head>
<title>Список контроллеров</title>
</head>
<body>
	<!-- @todo #189 Не отображается содержимое списка контроллеров -->
	<xsl:for-each select="controller">
	<a href="{concat('controllers/', @id}">
		<xsl:value-of select="address"/>
		<xsl:text>:</xsl:text>
		<xsl:value-of select="port"/>
	</a>
	<br/>
	</xsl:for-each>
</body>
</html>
</xsl:template>
</xsl:stylesheet>
