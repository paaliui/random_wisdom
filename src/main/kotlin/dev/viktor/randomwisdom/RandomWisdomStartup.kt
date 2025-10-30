package dev.viktor.randomwisdom

import com.intellij.openapi.project.Project
import com.intellij.openapi.startup.ProjectActivity
import com.intellij.openapi.application.ApplicationManager
import com.intellij.openapi.fileEditor.FileDocumentManagerListener

class RandomWisdomStartup : ProjectActivity {
    override suspend fun execute(project: Project) {
        val connection = ApplicationManager.getApplication().messageBus.connect(project)
        connection.subscribe(FileDocumentManagerListener.TOPIC, RandomWisdomListener(project))
    }
}
