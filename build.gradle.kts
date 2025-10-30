plugins {
    id("org.jetbrains.kotlin.jvm") version "2.2.0"
    id("org.jetbrains.intellij.platform") version "2.10.2"
}

group = providers.gradleProperty("pluginGroup").get()
version = providers.gradleProperty("pluginVersion").get()

repositories {
    mavenCentral()
    intellijPlatform {
        defaultRepositories()
    }
}

dependencies {
    intellijPlatform {
        clion(providers.gradleProperty("platformVersion"))
    }
    implementation(kotlin("stdlib"))
}

intellijPlatform {
    pluginConfiguration {
        version.set(providers.gradleProperty("pluginVersion"))
        ideaVersion {
            sinceBuild.set(providers.gradleProperty("pluginSinceBuild"))
            untilBuild.set(providers.gradleProperty("pluginUntilBuild"))
        }
    }
    instrumentCode = false
}

tasks {
    patchPluginXml {
        sinceBuild.set(providers.gradleProperty("pluginSinceBuild"))
        untilBuild.set(providers.gradleProperty("pluginUntilBuild"))
        changeNotes.set(
            """
<ul>
  <li>Первый релиз плагина Random Wisdom для CLion 2025.2.1.</li>
  <li>Показывает случайные «мудрости» при сохранении файла.</li>
  <li>Добавлен переключатель: Tools → Random Wisdom → Toggle Random Wisdom.</li>
  <li>Совместимость: Gradle 8.14.1, Kotlin 2.2.0, JVM target 21.</li>
  <li>Отключено инструментирование кода (instrumentCode=false) для стабильной сборки.</li>
  <li>Исправлена ошибка сборки buildSearchableOptions на CLion 2025.2.x.</li>
</ul>
""".trimIndent()
        )
    }
    withType<org.jetbrains.kotlin.gradle.tasks.KotlinCompile> {
        compilerOptions.jvmTarget.set(org.jetbrains.kotlin.gradle.dsl.JvmTarget.JVM_21)
        compilerOptions.languageVersion.set(org.jetbrains.kotlin.gradle.dsl.KotlinVersion.KOTLIN_2_2)
        compilerOptions.apiVersion.set(org.jetbrains.kotlin.gradle.dsl.KotlinVersion.KOTLIN_2_2)
    }
    withType<JavaCompile> {
        sourceCompatibility = "21"
        targetCompatibility = "21"
    }
    // CLion 2025.2.x: задача падает и не нужна нашему плагину — отключаем
    buildSearchableOptions {
        enabled = false
    }
}
