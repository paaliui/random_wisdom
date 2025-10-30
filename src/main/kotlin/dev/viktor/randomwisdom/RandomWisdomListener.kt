package dev.viktor.randomwisdom

import com.intellij.notification.NotificationGroupManager
import com.intellij.notification.NotificationType
import com.intellij.openapi.application.ApplicationManager
import com.intellij.openapi.fileEditor.FileDocumentManagerListener
import com.intellij.openapi.project.Project
import com.intellij.ide.util.PropertiesComponent

class RandomWisdomListener(private val project: Project) : FileDocumentManagerListener {
    private val phrases = listOf(
        "Где падает тест — там и баг.",
        "Пиши код просто, а не геройски.",
        "Стало быстрее? Докажи профилировщиком.",
        "Сначала напиши — потом отрефактори.",
        "Комментарий — костыль. Код — объяснение.",
        "Не бойся удалять код. Страшнее, когда он остаётся.",
        "Оптимизация до профилирования — мать всех багов.",
        "Тот, кто не делает бэкапы, ещё просто не терял данные.",
        "Каждый println — это мольба о помощи.",
        "Если работает — не трогай. Если не работает — не паникуй.",
        "Скорость написания кода не важна. Важно, как быстро ты его понимаешь завтра.",
        "Когда баг исчез сам — он вернётся с друзьями.",
        "Джун ищет ошибку в коде. Сеньор — в логике.",
        "Хороший программист пишет код, который поймёт плохой программист.",
        "Сначала всё работает, потом тесты, потом деплой, потом — реальность.",
        "Смерть от StackOverflow — почётная смерть.",
        "Если код невозможно сломать — значит, ты просто плохо старался.",
        "Баг, которого не видно, — самый опасный.",
        "Код, который не читают, становится легендой.",
        "Пиши так, будто следующий, кто будет читать код, знает, где ты живёшь."
    )

    private fun isEnabled(): Boolean =
        PropertiesComponent.getInstance().getBoolean("randomWisdom.enabled", true)

    override fun beforeDocumentSaving(document: com.intellij.openapi.editor.Document) {
        if (!isEnabled()) return

        val phrase = phrases.random()
        ApplicationManager.getApplication().invokeLater {
            NotificationGroupManager.getInstance()
                .getNotificationGroup("RandomWisdom")
                .createNotification(phrase, NotificationType.INFORMATION)
                .notify(project)
        }
    }
}
