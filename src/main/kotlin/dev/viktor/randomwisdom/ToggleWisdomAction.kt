package dev.viktor.randomwisdom

import com.intellij.notification.NotificationGroupManager
import com.intellij.notification.NotificationType
import com.intellij.ide.util.PropertiesComponent
import com.intellij.openapi.actionSystem.AnAction
import com.intellij.openapi.actionSystem.AnActionEvent

class ToggleWisdomAction : AnAction() {
    override fun actionPerformed(e: AnActionEvent) {
        val props = PropertiesComponent.getInstance()
        val enabled = props.getBoolean("randomWisdom.enabled", true)
        props.setValue("randomWisdom.enabled", (!enabled), true)

        val status = if (!enabled) "enabled" else "disabled"
        NotificationGroupManager.getInstance()
            .getNotificationGroup("RandomWisdom")
            .createNotification("Random Wisdom: $status", NotificationType.INFORMATION)
            .notify(e.project)
    }
}
