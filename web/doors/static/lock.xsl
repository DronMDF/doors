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
	<!-- @todo #195 Состояние замка хранится в БД и пробрасывается через API -->
	Состояние замка: неизвестно
</body>
</html>
</xsl:template>
</xsl:stylesheet>
